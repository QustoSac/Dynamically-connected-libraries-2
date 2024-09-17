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
