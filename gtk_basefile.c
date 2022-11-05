#include <gtk/gtk.h>

static void
oneplayerpressed (GtkWidget *widget,
                   gpointer   data)
{
    g_print ("helloworld\n");
}


static void
twoplayerpressed (GtkWidget *widget,
                   gpointer   data)
{
    g_print ("goodbyeworld\n");
}


static void
htppressed (GtkWidget *widget,
            gpointer   data)
{
    g_print ("world\n");
}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *oneplayer;
  GtkWidget *twoplayer;
  GtkWidget *htp;
  
  //new window with title//
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Tic Tac Toe");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  gtk_widget_show (window);

  //construct the container that is going pack our buttons//
  grid = gtk_grid_new ();

  //Pack the container in the window//
  gtk_window_set_child (GTK_WINDOW (window), grid);

  //oneplayer button//
  /*gtk_grid_attach: horizontal,vertical,size_horizontal,size_vertical*/
  oneplayer = gtk_button_new_with_label ("player vs AI");
  g_signal_connect (oneplayer, "clicked", G_CALLBACK (oneplayerpressed), NULL);
  gtk_grid_attach (GTK_GRID (grid), oneplayer, 0, 0, 1, 1);

  //twoplayer button//
  /*gtk_grid_attach: horizontal,vertical,size_horizontal,size_vertical*/
  twoplayer = gtk_button_new_with_label ("player vs player");
  g_signal_connect (twoplayer, "clicked", G_CALLBACK (twoplayerpressed), NULL);
  gtk_grid_attach (GTK_GRID (grid), twoplayer, 0, 1, 1, 1);

  //how to play button//
  htp = gtk_button_new_with_label ("how to play");
  g_signal_connect (htp, "clicked", G_CALLBACK(htppressed), NULL);
  gtk_grid_attach(GTK_GRID (grid), htp, 0, 2, 1, 1);

}





//to set the code as an app//
int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
