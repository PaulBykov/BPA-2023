Курсовой защищён на отметку 10, причём его особо не смотрели.
Задание 34241:
<ul>
  <li>Типы данных: целочисленный, символьный. Дополнительно: логический, строковый</li>
  <li>Операции сравненения: >, <, ==, !=, >=, <=. Дополнительно: +, - </li>
  <li>Литералы: логические, строковые, символьные. Дополнительно: целые (10-ричное) </li>
  <li>Функции стандартной библиотеки: лексикографическое сравнение строк; возведение числа в степень</li>
  <li>Инструкции: ветвление, цикла</li>
  <li>Дополнительно: <b> константы </b>, комментарии, система тестирования, свой синтаксис для notepad++ </li>
</ul>

<h2>Как украсть?</h2>
<ul>
  <li>Качаем репозиторий</li>
  <li>В настройках проекта меняем выходной каталог на путь до папки result</li>
  <li>В проекте BPA-testing меняет значение двух констант на пути до .exe файла, и до папки с тестовыми данными (result/TEST_CASES)</li>
</ul>
<h2>Известные проблемы</h2>
<ul>
  <li>Осторожнее со вложеностью конструкций, например if внутри if скорее всего будет приводить к ошибке в ассемблере, это исправляется изменением флагов в CodeGeneration.cpp из логических в целочисленные.</li>
  <li>Вызов функции в другой функции иногда вызывает ошибку, а иногда нет, как показано в test_2.txt</li>
  <li>Местами вставленны костыли, например в лексическом анализе при логических литералах. При внесеннии изменений будьте бдительны!</li>
  <li>У курсача была гнилая основа, а потому и возникали многие трудности, вам осталось переписать не так много, и будет счастье не только вам, но и будующим поколениям.</li>
</ul>
<h3>Если вам нужна будет помощь, можете обращаться по контактам в профиле гитхаба.</h3>