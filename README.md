# Системное программирование. Задание. Библиотека DLL

Этот проект демонстрирует использование динамических библиотек в Linux на примере библиотеки, содержащей функцию `TestHello`, которая вызывает диалоговое окно, используя библиотеку `GTK+`. Программа включает несколько файлов, которые взаимодействуют с динамическими библиотеками (`.so`), а также графический интерфейс для отображения сообщения, аналогичного `MessageBox` в Windows.

## Структура проекта

- `testfunc.cpp`: Реализация функции `TestHello`, которая отображает диалоговое окно с сообщением с использованием библиотеки `GTK+`.
- `dllmain.cpp`: Главная программа, которая вызывает функцию `TestHello` из динамической библиотеки.
- `libtestfunc.so`: Скомпилированная динамическая библиотека, содержащая функцию `TestHello`.

## Требования

Для сборки и запуска проекта необходимо установить следующие пакеты:

- **g++** (компилятор для C++)
- **GTK+** (для отображения графического интерфейса)

### Установка зависимостей (на Ubuntu):

```bash
sudo apt-get update
sudo apt-get install g++ libgtk-3-dev
```
## Компиляция
Сначала скомпилируйте динамическую библиотеку libtestfunc.so:
```bash
g++ -fPIC -shared -o libtestfunc.so testfunc.cpp `pkg-config --cflags --libs gtk+-3.0`
```
Затем скомпилируйте основной файл программы main.cpp:
```bash
g++ -o main dllmain.cpp -L. -ltestfunc `pkg-config --cflags --libs gtk+-3.0`
```
## Запуск
Перед запуском программы убедитесь, что динамическая библиотека доступна для загрузки. Если она находится в текущей директории, добавьте её в переменную окружения LD_LIBRARY_PATH:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
```

#### Запустите программу:

```bash
./main
```
![image](https://github.com/user-attachments/assets/67cec968-6801-430a-8861-0ae1bbfbd2c4)

## Описание
#### testfunc.cpp
Файл testfunc.cpp содержит реализацию функции TestHello, которая использует библиотеку GTK+ для отображения диалогового окна с сообщением.
```
#include <gtk/gtk.h>

// Функция, которая покажет окно с сообщением
extern "C" void TestHello(void) {
    gtk_init(0, nullptr);  // Инициализация GTK

    GtkWidget *dialog;
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Создание родительского окна

    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Hello, you're calling a function in this shared library!");
    gtk_window_set_title(GTK_WINDOW(dialog), "DLL Skeleton");

    gtk_dialog_run(GTK_DIALOG(dialog));  // Показываем диалог
    gtk_widget_destroy(dialog);          // Удаляем диалог

    gtk_widget_destroy(window);  // Удаление окна
}
```

#### dllmain.cpp
Файл dllmain.cpp вызывает функцию TestHello из динамической библиотеки libtestfunc.so, которая была скомпилирована на предыдущем шаге.
```
#include <iostream>

extern "C" void TestHello(void);

int main() {
    std::cout << "Calling TestHello from shared library..." << std::endl;
    
    TestHello();
    
    return 0;
}
```




