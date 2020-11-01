#include <stdio.h>

#include <gtk/gtk.h>

static void activate (GtkApplication* app, gpointer user_data) {
	GtkWidget* scrolled_window1 = gtk_scrolled_window_new (NULL, NULL);
	GtkWidget* scrolled_window2 = gtk_scrolled_window_new (NULL, NULL);
	
	GtkWidget* window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Gtk Error Handler");
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
	gtk_container_add (GTK_CONTAINER (window), scrolled_window1);
	// This produces a Gtk-WARNING, as it is not allowed to add two
	// children to the window.
	gtk_container_add (GTK_CONTAINER (window), scrolled_window2);
	gtk_widget_show_all (window);
}

void my_log_handler (const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data) {
	printf("We got a log message: %s\n", message);
}

int main (int argc, char **argv) {
	gtk_init (&argc, &argv);
	
	//g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, my_log_handler, NULL); //Catch WARNING
	g_log_set_handler ("Gtk", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, my_log_handler, NULL); //Catch all
	g_log ("Gtk", G_LOG_LEVEL_WARNING, "This is a test message");
	
	GtkApplication *app = gtk_application_new ("com.github.BenjaminRi.gtk_error_handler", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	int status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	
	return status;
}
