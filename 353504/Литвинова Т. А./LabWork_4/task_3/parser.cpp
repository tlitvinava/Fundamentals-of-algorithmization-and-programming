#include <INCLUDES.h>

Parser::Parser(string &&str) : _str(std::move(str))
{
    _searchVariables();
    _searchFunctions();
}

vector<Variable> Parser::getVariables()
{
    return _variables;
}

vector<Functions> Parser::getFunctions()
{
    return _functions;
}

pair<int, int> Parser::searchInfiniteLoops()
{
    smatch sm;
    regex reg1("while\\s*\\((true|false|1|0)\\)\\s*\\{"); // Регулярное выражение для поиска бесконечных циклов

    string searchStr = _str; // Копия строки для поиска
    int lineNumber = 0; // Номер строки, содержащей бесконечный цикл
    int charPosition = 0; // Позиция символа в строке, содержащей бесконечный цикл
    auto lines = QString::fromStdString(_str).split('\n'); // Разделение строки на строки по символу новой строки

    while (regex_search(searchStr, sm, reg1)) // Поиск бесконечных циклов в строке
    {
        lineNumber = 0;
        charPosition = sm.position() + 1; // Получение позиции символа начала бесконечного цикла

        for (const auto& line : lines) { // Поиск строки, содержащей бесконечный цикл
            lineNumber++;
            if (lineNumber == 1) { // Пропускаем первую строку и корректируем позицию символа в строке
                if (charPosition <= line.length()) {
                    break;
                } else {
                    charPosition -= line.length();
                    continue;
                }
            }
            charPosition += line.length() + 1;
            if (charPosition > sm.position() + 1) {
                break;
            }
        }

        return make_pair(lineNumber, charPosition); // Возвращаем номер строки и позицию символа
        searchStr = sm.suffix(); // Продолжаем поиск в оставшейся части строки
    }

    // Если никаких ошибок не найдено, возвращаем (-1, -1)
    return make_pair(-1, -1);
}

void Parser::_searchFunctions()
{
    // Инициализация переменных и регулярных выражений
    smatch match, match2, match3, match4;

    string inputStr = _str;
    // Регулярное выражение для поиска функций
    regex functionRegex("(int|float|double|short|long\\slong|char|bool|void|string)\\s+(\\w+)\\s*\\((.*)\\)");
    // Регулярное выражение для поиска аргументов функций
    regex argumentRegex("(int|float|double|short|long\\slong|char|bool|void|string)\\s+\\w*,?");

    while (std::regex_search(inputStr, match, functionRegex)) {
        bool isOverload = false;

        for (size_t i = 0; i < _functions.size(); i++) {
            if (match[2].str() == _functions[i].getName()) {
                isOverload = true;
                break;
            }
        }

        if (isOverload) {
            inputStr = match.suffix();
            continue;
        }

        // Регулярное выражение для поиска возвращаемого типа функции
        regex returnTypeRegex("(int|float|double|short|long\\slong|char|bool|void|string)");
        // Регулярное выражение для поиска сигнатуры функции
        regex functionSignatureRegex("(int|float|double|short|long\\slong|char|bool|void|string)\\s+" + match[2].str() + "\\s*\\((.*)\\)");
        vector<pair<int, int>> argumentPositions;
        vector<string> arguments, overloadArguments;
        vector<Functions> overloadFunctions;
        string argumentsStr = match[3].str();
        auto lines = QString::fromStdString(inputStr).split('\n');
        int overloadCount = 0;

        while (regex_search(argumentsStr, match2, argumentRegex)) {
            arguments.push_back(match2[1].str());
            argumentsStr = match2.suffix();
        }

        for (auto i = 0; i < lines.length(); i++) {
            auto line = lines[i].toStdString();

            while (regex_search(line, match3, functionSignatureRegex)) {
                if (overloadCount != 0) {
                    argumentPositions.push_back(std::make_pair(i + 1, match2.position() + 1));

                    string overloadArgumentsStr = match3[2].str();
                    overloadArguments.clear();

                    while (std::regex_search(overloadArgumentsStr, match4, argumentRegex)) {
                        overloadArguments.push_back(match4[1].str());
                        overloadArgumentsStr = match4.suffix();
                    }

                    overloadFunctions.push_back(Functions(match3[1].str(), match[2].str(), overloadArguments));
                }
                overloadCount++;
                line = match3.suffix();
            }
        }
        _functions.push_back(Functions(match[1].str(), match[2].str(), overloadFunctions, arguments));
        inputStr = match.suffix();
    }
}



vector<int> Parser::getComplexStructs()
{
    smatch classMatch, structMatch, arrayMatch, staticArrayMatch; // Переименование переменных для более ясного понимания их назначения

    regex classRegex("(class)\\s+(\\w+)\\s*\\{"); // Переименование регулярного выражения для поиска классов
    regex structRegex("(struct)\\s+(\\w+)\\s*\\{"); // Переименование регулярного выражения для поиска структур
    regex arrayRegex("(\\w+)\\s*[*]\\s*(\\w+)\\s*[=]\\s*(new)\\s*(\\w+)\\s*(\\[)\\s*(\\w+|\\d+)\\s*(\\])"); // Переименование регулярного выражения для поиска динамических массивов
    regex staticArrayRegex("(int|float|double|short|long\\slong|char|bool|void|string)\\s*(\\w+)\\s*(\\[)\\s*(\\d+)\\s*(\\])"); // Переименование регулярного выражения для поиска статических массивов

    vector<int> counter(4); // Переименование вектора для хранения счетчиков
    string strToSearch = _str; // Переименование временной строки для хранения оригинальной строки

    while (regex_search(strToSearch, classMatch, classRegex)) { // Цикл поиска классов
        strToSearch = classMatch.suffix();
        counter[0] += 1;
    }

    strToSearch = _str;

    while (regex_search(strToSearch, structMatch, structRegex)) { // Цикл поиска структур
        strToSearch = structMatch.suffix();
        counter[1] += 1;
    }

    strToSearch = _str;

    while (regex_search(strToSearch, arrayMatch, arrayRegex)) { // Цикл поиска динамических массивов
        strToSearch = arrayMatch.suffix();
        counter[2] += 1;
    }

    strToSearch = _str;

    while (regex_search(strToSearch, staticArrayMatch, staticArrayRegex)) { // Цикл поиска статических массивов
        strToSearch = staticArrayMatch.suffix();
        counter[3] += 1;
    }

    return counter; // Возвращаем вектор с счетчиками
}


vector<pair<int, int>> Parser::getChangePosition()
{
    smatch match; // Инициализация объекта match для хранения результатов поиска с помощью регулярных выражений
    regex pattern("(\\s*(\\S*=\\s*(\\w+))?\\s*;)"); // Определение регулярного выражения для поиска
    vector<pair<int, int>> positions;        // Вектор для хранения позиций изменений
    auto lines = QString::fromStdString(_str).split('\n'); // Преобразование строки _str в QString и разделение на строки по символу '\n'
    int lineIndex = 0;                       // Индекс текущей строки

    for (auto i = 0; i < lines.length(); i++) { // Цикл по строкам
        auto currentLine = lines[i].toStdString(); // Преобразование текущей строки в std::string

        while (regex_search(currentLine, match, pattern)) { // Цикл поиска подстрок, соответствующих регулярному выражению
            if (lineIndex != 0) { // Если индекс текущей строки не равен 0, то добавляем позицию изменения в вектор
                positions.push_back(make_pair(i + 1, match.position() + 1));
            }
            lineIndex++; // Увеличиваем индекс текущей строки
            currentLine = match.suffix(); // Присваиваем оставшуюся часть строки после найденного совпадения
        }
    }
    return positions; // Возвращаем вектор с позициями изменений
}

vector<pair<int,int>> Parser::getBranches()
{
    smatch sm;
    string inputStr = _str;
    regex branchRegex("(((if|if else)\\s*(\\()(.*)(\\))\\s*)|else)(\\{)"); // Регулярное выражение для поиска ветвлений

    vector<int> branchPositions; // Вектор для хранения позиций ветвлений
    int currentPosition = 0; // Переменная для отслеживания текущей позиции во входной строке

    // Цикл для нахождения позиций ветвлений во входной строке
    while(regex_search(inputStr, sm, branchRegex)){
        branchPositions.push_back(currentPosition + sm.position(0)); // Сохраняем позицию текущего ветвления
        currentPosition += sm.prefix().length() + sm.length(); // Обновляем текущую позицию до конца найденного совпадения
        inputStr = sm.suffix(); // Обновляем входную строку до суффикса текущего совпадения
    }

    int bracketsCounter; // Переменная для отслеживания количества встреченных скобок
    vector<pair<int,int>> bracketPositions; // Вектор для хранения позиций скобок и их соответствующих счетчиков скобок

    inputStr = _str; // Сбрасываем входную строку до исходного значения

    // Цикл по найденным позициям ветвлений для определения соответствующих позиций закрывающих скобок и их счетчиков
    for(size_t i = 0; i < branchPositions.size(); i++){
        int pos = branchPositions[i]; // Получаем позицию текущего ветвления
        bracketsCounter = 2; // Инициализируем счетчик скобок значением 2, предполагая, что ветвление начинается с '{'
        pair<int,int> tmp1(pos, bracketsCounter); // Создаем пару для хранения позиции и счетчика скобок
        bracketPositions.push_back(tmp1); // Добавляем пару в вектор позиций скобок

        // Цикл для нахождения соответствующей закрывающей скобки и ее счетчика
        while(bracketsCounter != 1){
            if(branchPositions[i+1] == pos){
                i++; // Переходим к следующему ветвлению, если позиция совпадает с текущим ветвлением
                bracketsCounter++; // Увеличиваем счетчик скобок для вложенных ветвлений
                pair<int,int> tmp(pos, bracketsCounter); // Создаем пару для хранения позиции и счетчика скобок
                bracketPositions.push_back(tmp); // Добавляем
                continue; // Пропускаем текущую итерацию и переходим к следующей
            }

            if(inputStr[pos] == '{'){
                bracketsCounter++; // Увеличиваем счетчик открывающих скобок
            }
            else if(inputStr[pos] == '}'){
                bracketsCounter--; // Уменьшаем счетчик закрывающих скобок
            }
            pos++; // Переходим к следующему символу во входной строке
        }

        pair<int,int> tmp2(pos-1, bracketsCounter); // Создаем пару для хранения позиции и счетчика скобок
        bracketPositions.push_back(tmp2); // Добавляем пару в вектор позиций скобок
    }

    return bracketPositions; // Возвращаем вектор пар с позициями скобок и их счетчиками
}

void Parser::_searchVariables()
{
    regex variableRegex("((int|float|double|short|long\\slong|char|bool|void|string)\\s(\\w+)\\s*(=\\s*(\\w+))?\\s*;)"); // Регулярное выражение для поиска переменных
    smatch variableMatch, subMatch; // Матчеры для переменных и подвыражений
    string str = _str; // Исходная строка для поиска
    int lineSizeTmp = 0; // Размер текущей строки

    while(regex_search(str, variableMatch, variableRegex)){
        regex subRegex(variableMatch[3].str() + "(\\s*(\\S*=\\s*(\\w+))?\\s*;)"); // Регулярное выражение для поиска подвыражений переменной
        vector<pair<int,int>> position; // Позиция переменной в исходной строке
        auto stringTemp = QString::fromStdString(str).split('\n'); // Разбиение исходной строки на строки
        int varCount = 0; // Счетчик переменных

        for(auto i = 0; i < stringTemp.length(); i++){
            auto line = stringTemp[i].toStdString(); // Текущая строка

            while(regex_search(line, subMatch, subRegex)){
                if(varCount != 0){
                    position.push_back(make_pair(i+1, subMatch.position() + 1)); // Запись позиции переменной в вектор позиций
                }
                varCount++;
                line = subMatch.suffix();
            }
        }

        int bracketsCounter = 0; // Счетчик фигурных скобок
        qDebug() << variableMatch.prefix().length();
        for(auto i = 0; i < variableMatch.prefix().length() + lineSizeTmp; i++){
            if(_str[i] == '{'){
                bracketsCounter++;
            }
            if(_str[i] == '}'){
                bracketsCounter--;
            }
        }
        lineSizeTmp += variableMatch.prefix().length();

        _variables.push_back(Variable(variableMatch[2].str(), variableMatch[3].str(), position, variableMatch[5].str(), !bracketsCounter)); // Создание объекта Variable и добавление его в вектор _variables
        str = variableMatch.suffix();
    }
}
