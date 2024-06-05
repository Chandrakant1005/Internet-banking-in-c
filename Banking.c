#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE 1000

GtkWidget *home_page();

FILE *USER_DETAILS;
FILE *USER_PASS;
FILE *last_cus_id;
FILE *PERSONAL_DETAILS;

GtkStack *stack ;
char cust_id_pass[50];
struct update_homepage{

    GtkWidget *name_label;
    GtkWidget *cust_id;
    GtkWidget *name;
    GtkWidget *phone_no;
    GtkWidget *balance;
};


struct user_det{
    int customer_id;
    char first_name[50];
    char last_name[50];
    int balance;
};


struct user_pass{
    GtkWidget *c_id;
    GtkWidget *pass;
};


struct reg_struct{
    int cus_id;
    GtkWidget *f_name;
    GtkWidget *l_name;
    GtkWidget *p_no;
    GtkWidget *pass;
    GtkWidget *cpass;

};


struct reg_struct reg_d;
struct user_pass pass_entry;
struct update_homepage update_home;
int details_extr(FILE *file ,char *search_string,char *line) {
    while (fgets(line, MAX_LINE, file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void update_h(){
             FILE *fp = fopen("current_user.txt","r");
             FILE *fp1 = fopen("user_datails.txt","r");
             char line[MAX_LINE];
             char hello[35];
             char cust_id[100];
             fscanf(fp,"%s",cust_id);
             fclose(fp);
             details_extr(fp1,cust_id,line);
             char name[30];
             char phone[12];
             char balance[30];
             int i=0;
             int j;
             int cnt=0;
             while (line[i]!='\0')
             {
                if (line[i]=='-')
                {
                    cnt++;
                }
                i++;
                if (cnt == 1){   
                    j=0;
                    while (line[i]!='-'){
                       name[j]=line[i];j++;i++;}
                       name[j]='\0';
                       i--;
                }

                if (cnt == 2){
                    j=0;
                   while (line[i]!='-'){
                       phone[j]=line[i];j++;i++;
                    }
                    phone[j]='\0';

                    i--;
                }
                 if (cnt == 3){
                    j=0;
                   while (line[i]!='\0'){
                       balance[j]=line[i];j++;i++;
                    }
                    balance[j]='\0';
                    i--;
                }
                i++;
             }
             
             gtk_label_set_text(GTK_LABEL(update_home.name_label),name);
             gtk_label_set_text(GTK_LABEL(update_home.cust_id),cust_id);
             gtk_label_set_text(GTK_LABEL(update_home.name),name);
             gtk_label_set_text(GTK_LABEL(update_home.phone_no),phone);
             gtk_label_set_text(GTK_LABEL(update_home.balance),balance);

}
void border_maker(GtkWidget *label){
 GtkCssProvider *provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider,
        ".border {"
        "   border: 0.3px solid black;"
        "   padding: 10px;"
        "}", -1, NULL);
    

    GtkStyleContext *context = gtk_widget_get_style_context(label);
    gtk_style_context_add_class(context, "border");
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

}
void pass_incorrect_warning(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Warning Dialog");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK,
                                               "Username Password Doesn't match !");

    gtk_window_set_title(GTK_WINDOW(dialog), "Failed");

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);

}

int search_string_in_file(FILE *file ,const gchar *search_string) {
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
    
}
void already_registered(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Warning Dialog");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gchar *message = g_strdup_printf("Already Registered !\n    Try With login");

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK,
                                               "%s", message);

    gtk_window_set_title(GTK_WINDOW(dialog), "Failed");

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);
    g_free(message); 

}

void show_cust_id(int cust){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Warning Dialog");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gchar *message = g_strdup_printf("Registered Successfully !\n Customer ID: %d", cust);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK,
                                               "%s", message);

    gtk_window_set_title(GTK_WINDOW(dialog), "Success");

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);
    g_free(message); 

}
void show_warning_dialog_for_nul(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Warning Dialog");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK,
                                               "Please fill the required fields..");

    gtk_window_set_title(GTK_WINDOW(dialog), "Warning");

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);
}
void show_warning_dialog_for_pass() {

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Warning Dialog");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK,
                                               "Passwords doesn't match!");

    gtk_window_set_title(GTK_WINDOW(dialog), "Warning");

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);
}
gboolean is_entry_empty(const gchar *text) {
    return text[0] == '\0'; // Returns TRUE if empty, FALSE otherwise
}

void register_d(GtkWidget *widget, struct reg_struct *data){
    int n ;
    const gchar *fi_name = gtk_entry_get_text(GTK_ENTRY(data->f_name));
    const gchar *la_name = gtk_entry_get_text(GTK_ENTRY(data->l_name));
    const gchar *ph_no= gtk_entry_get_text(GTK_ENTRY(data->p_no));
    const gchar *pass_= gtk_entry_get_text(GTK_ENTRY(data->pass));
    const gchar *c_pass= gtk_entry_get_text(GTK_ENTRY(data->cpass));
    if(is_entry_empty(fi_name)||is_entry_empty(la_name)||is_entry_empty(ph_no)||
       is_entry_empty(pass_)||is_entry_empty(c_pass)){
        show_warning_dialog_for_nul();
    }
    else if (strcmp(pass_,c_pass))
    {
        show_warning_dialog_for_pass();
    }
    else{
        FILE *file = fopen("user_datails.txt","r");
        if(search_string_in_file(file,ph_no)){
          already_registered();

        }else{
    //FILE HANDLING
    USER_DETAILS = fopen("user_datails.txt","a");
    last_cus_id = fopen("last_cus_id.txt","r");
    USER_PASS = fopen("user_pass.txt","a");

    //customer id
    fscanf(last_cus_id, "%d", &n);
    n++;
    fclose(last_cus_id);
    last_cus_id = fopen("last_cus_id.txt","w");
    fprintf(last_cus_id, "%d", n);
    fclose(last_cus_id);

    //user details
    fprintf(USER_DETAILS, "%d-%s %s-%s-%d\n",n,fi_name,la_name,ph_no,0);


    fclose(USER_DETAILS);
    
    //user pass
    fprintf(USER_PASS,"%d%s\n", n,pass_);
    fclose(USER_PASS);
    
    show_cust_id(n);
    

    // Print the text to the console
    g_print("Text entered: %d\n", n);
    g_print("Text entered: %s\n", fi_name);
    g_print("Text entered: %s\n", la_name);
    g_print("Text entered: %s\n", ph_no);

     }
    }
}

void switch_to_login_page(GtkWidget *widget, gpointer data) {
    GtkStack *stack = GTK_STACK(data);
    gtk_stack_set_visible_child_name(stack, "login");
}

void switch_to_welcome_page(GtkWidget *widget, gpointer data) {
    GtkStack *stack = GTK_STACK(data);
    gtk_stack_set_visible_child_name(stack, "welcome");
}

void switch_to_signup_page(GtkWidget *widget, gpointer data) {
    GtkStack *stack = GTK_STACK(data);
    gtk_stack_set_visible_child_name(stack, "signup");
}

void switch_to_home_page(GtkWidget *widget,struct user_pass *entry) {
    FILE *c_user = fopen("current_user.txt","w");
    FILE *user_pass = fopen("user_pass.txt","r");
    const gchar *cust_id = gtk_entry_get_text(GTK_ENTRY(entry->c_id));
    const gchar *pass = gtk_entry_get_text(GTK_ENTRY(entry->pass));
    const gchar *message = g_strconcat(cust_id,pass,NULL);
    if (!search_string_in_file(user_pass,message))
    {
        pass_incorrect_warning();
    }else{
    fprintf(c_user,"%s",cust_id);
    fclose(c_user);
    update_h();
    GtkStack *stack1 = GTK_STACK(stack);
    gtk_stack_set_visible_child_name(stack1, "homepage");
    }
}
void switch_back_home(GtkWidget *widget,gpointer data){
      GtkStack *stack = GTK_STACK(data);
      gtk_stack_set_visible_child_name(stack, "homepage");
}

void switch_to_withdrawl_page(GtkWidget *widget, gpointer data){
      GtkStack *stack = GTK_STACK(data);
      gtk_stack_set_visible_child_name(stack, "withdrawl");

}

GtkWidget *welcome_page(){
      
      GtkWidget *vboxw = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

      GtkWidget *label1 = gtk_label_new("WELCOME TO INTERNET BANKING");
      GtkWidget *label2 = gtk_label_new("Already account !");
      GtkWidget *button_l = gtk_button_new_with_label("Sign In ");
      //button event handling
      g_signal_connect(button_l, "clicked", G_CALLBACK(switch_to_login_page), stack);

      GtkWidget *label3 = gtk_label_new("Not Have Account. Register here !");  
      GtkWidget *button_s = gtk_button_new_with_label("Sign Up ");
      //button event handling
      g_signal_connect(button_s, "clicked", G_CALLBACK(switch_to_signup_page), stack);
      

      gtk_box_pack_start(GTK_BOX(vboxw),label1, FALSE, FALSE, 50);
      gtk_box_pack_start(GTK_BOX(vboxw),label2, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(vboxw),button_l, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(vboxw),label3, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(vboxw),button_s, FALSE, FALSE, 5);
    g_print(cust_id_pass);
      
      return vboxw;
}

GtkWidget *login_page(){


     GtkWidget *vboxl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
     GtkWidget *label1_l = gtk_label_new("LOGIN HERE");
     GtkWidget *label2_l = gtk_label_new("CUSTOMER ID ");
     GtkWidget *entry1= gtk_entry_new();
     gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Enter customer id here...");
     GtkWidget *label3_l = gtk_label_new("PASSWORD ");
     GtkWidget *entry2= gtk_entry_new();
     gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Enter password here...");

     pass_entry.c_id = entry1;
     pass_entry.pass = entry2;
     GtkWidget *button_ll = gtk_button_new_with_label("Log In ");
     g_signal_connect(button_ll, "clicked", G_CALLBACK(switch_to_home_page),&pass_entry);
     GtkWidget *button_b = gtk_button_new_with_label("<- BACK  ");
     g_signal_connect(button_b, "clicked", G_CALLBACK(switch_to_welcome_page), stack);
     
     gtk_box_pack_start(GTK_BOX( vboxl),label1_l, FALSE, FALSE, 50);
     gtk_box_pack_start(GTK_BOX( vboxl),label2_l, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX( vboxl),entry1, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX( vboxl),label3_l, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX( vboxl),entry2, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX( vboxl),button_ll, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX( vboxl),button_b, FALSE, FALSE, 5);
     
     
     return vboxl;
}

GtkWidget *signup_page(){
   
    GtkWidget *vboxs = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    

    GtkWidget *label1_s = gtk_label_new("Sign Up Here !");
    
    GtkWidget *hboxs1   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label2_s = gtk_label_new("First Name");   
    GtkWidget *label3_s = gtk_label_new("Last Name");
    gtk_widget_set_margin_start(label2_s, 5); 
    gtk_widget_set_margin_start(label3_s, 230);
    gtk_box_pack_start(GTK_BOX(hboxs1),label2_s, FALSE, FALSE, 0);  
    gtk_box_pack_start(GTK_BOX(hboxs1),label3_s, FALSE, FALSE, 0);

    GtkWidget *hboxs2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); 
    GtkWidget *entry1=  gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "FIRST NAME HERE");
    GtkWidget *entry2= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "LAST NAME HERE");
    gtk_box_pack_start(GTK_BOX(hboxs2),entry1, TRUE, TRUE, 5);   
    gtk_box_pack_start(GTK_BOX(hboxs2),entry2, FALSE, FALSE, 5);   
    
    GtkWidget *label4_s = gtk_label_new("Phone Number");
    gtk_widget_set_margin_start(label4_s, 5);
    GtkWidget *entry3= gtk_entry_new();

    GtkWidget *label5_s = gtk_label_new("Password");
    gtk_widget_set_margin_start(label4_s, 5);
    GtkWidget *entry4= gtk_entry_new();

    GtkWidget *label6_s = gtk_label_new("Confirm Password");
    gtk_widget_set_margin_start(label4_s, 5);
    GtkWidget *entry5= gtk_entry_new();

    reg_d.f_name = entry1;
    reg_d.l_name = entry2;
    reg_d.p_no = entry3;
    reg_d.pass = entry4;
    reg_d.cpass = entry5;
    
    
 
    GtkWidget *button_r = gtk_button_new_with_label("REGISTER  ");
    g_signal_connect(button_r, "clicked", G_CALLBACK(register_d),&reg_d);


    GtkWidget *button_b = gtk_button_new_with_label("<- BACK  ");
    g_signal_connect(button_b, "clicked", G_CALLBACK(switch_to_welcome_page), stack);

     gtk_box_pack_start(GTK_BOX(vboxs),label1_s, FALSE, FALSE, 30);
     gtk_box_pack_start(GTK_BOX(vboxs),hboxs1, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX(vboxs),hboxs2, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX(vboxs),label4_s, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(vboxs),entry3, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX(vboxs),label5_s, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(vboxs),entry4, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX(vboxs),label6_s, FALSE, FALSE, 0);
     gtk_box_pack_start(GTK_BOX(vboxs),entry5, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX(vboxs),button_r, FALSE, FALSE, 5);
     gtk_box_pack_start(GTK_BOX(vboxs),button_b, FALSE, FALSE, 5);
     

     return vboxs;
}

GtkWidget *home_page(){
    FILE *c_user = fopen("current_user.txt","r");
    char cust_id[20];
    fscanf(c_user,"%s",cust_id);
    fclose(c_user);
     GtkWidget *vboxl = gtk_grid_new();

         GtkWidget *button1 = gtk_button_new_with_label("<-");
         g_signal_connect(button1, "clicked", G_CALLBACK(switch_to_welcome_page), stack);
     
         GtkWidget *label_1 = gtk_label_new(NULL);
         GtkWidget *label_s = gtk_label_new(NULL);
         border_maker(label_1);
         GtkWidget *label_2 = gtk_label_new("Customer Id ");
         border_maker(label_2);
         GtkWidget *label_2h = gtk_label_new(NULL);
         border_maker(label_2h);

         GtkWidget *label_3 = gtk_label_new("Username");
         border_maker(label_3);
         GtkWidget *label_3h = gtk_label_new(NULL);
         border_maker(label_3h);
         
         GtkWidget *label_4 = gtk_label_new("Phone No.");
         border_maker(label_4);
         GtkWidget *label_4h = gtk_label_new("7500832015");
         border_maker(label_4h);
         
         GtkWidget *label_5 = gtk_label_new("Balance ");
         border_maker(label_5);
         GtkWidget *label_5h = gtk_label_new(" ");
         border_maker(label_5h);
        
         GtkWidget *button_w = gtk_button_new_with_label("Withdrawl");
         g_signal_connect(button_w, "clicked", G_CALLBACK(switch_to_withdrawl_page), stack);
         GtkWidget *label_s1 = gtk_label_new("  " );
         GtkWidget *button_d = gtk_button_new_with_label("Deposit");

         update_home.name_label = label_1;
         update_home.cust_id = label_2h;
         update_home.name = label_3h;
         update_home.phone_no= label_4h;
         update_home.balance = label_5h;


         gtk_widget_set_hexpand(label_1, TRUE);
         gtk_widget_set_halign(label_1, GTK_ALIGN_FILL);
         gtk_grid_set_column_spacing(GTK_GRID(vboxl), 10);
         gtk_grid_set_row_spacing(GTK_GRID(vboxl), 10);
         gtk_grid_attach(GTK_GRID(vboxl), button1,  1, 1, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_1,  2, 1, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_s,  1, 2, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_2,  1, 3, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_2h, 2, 3, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_3,  1, 4, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_3h, 2, 4, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_4,  1, 5, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_4h, 2, 5, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_5,  1, 6, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_5h, 2, 6, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_s1,  1, 7, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), button_w, 1, 8, 2, 1);
         gtk_grid_attach(GTK_GRID(vboxl), button_d, 1, 9, 2, 1);
          


       
          return vboxl;
}

void update_balance(){
FILE *fuser = fopen("user_datails.txt","w+");
char line[100];
int lcnt = 0;
int scnt = 0 ;
 while (fgets(line, MAX_LINE, fuser) != NULL) {
        lcnt++;
        if (strstr(line, search_string) != NULL) {
            break;
        }}
        

        
        
        
        
        }

GtkWidget *Withdrawl(){
       
         GtkWidget *vboxl = gtk_grid_new();

         GtkWidget *button1 = gtk_button_new_with_label("<-");
         
         g_signal_connect(button1, "clicked", G_CALLBACK(switch_back_home), stack);
        
         GtkWidget *label_1 = gtk_label_new("Withdrawl Here");
         GtkWidget *label_s = gtk_label_new(NULL);
         GtkWidget *label_3 = gtk_label_new("Current Balance");
         GtkWidget *label_3h = gtk_label_new("0");
         GtkWidget *label_s1 = gtk_label_new(NULL);
         GtkWidget *entry1=  gtk_entry_new();
         gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Enter amount to Withdrawl ");
         GtkWidget *buttonw = gtk_button_new_with_label("Withdrawl");
         
         border_maker(label_1);
         border_maker(label_3);
         border_maker(label_3h);
         gtk_widget_set_hexpand(label_1, TRUE);
         gtk_widget_set_halign(label_1, GTK_ALIGN_FILL);
         gtk_grid_set_column_spacing(GTK_GRID(vboxl), 10);
         gtk_grid_set_row_spacing(GTK_GRID(vboxl), 10);
         gtk_grid_attach(GTK_GRID(vboxl), button1,  1, 1, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_1,  2, 1, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_s,  1, 2, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_3,  1, 3, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_3h, 2, 3, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), label_s1, 1, 4, 1, 1);
         gtk_grid_attach(GTK_GRID(vboxl), entry1,   1, 5, 2, 1);
         gtk_grid_attach(GTK_GRID(vboxl), buttonw,  1, 6, 2, 1);
         
         return vboxl;


}




int main(int argc, char *argv[]) {
    GtkWidget *vbox;
    gtk_init(&argc, &argv);



    //GTK MAIN WINDOW
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "INTERNET BANKING");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 500,500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GdkPixbuf *icon = gdk_pixbuf_new_from_file("danu.png", NULL);
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    //STACK 
    stack = GTK_STACK(gtk_stack_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(stack));


    //Stack Management
     
    gtk_stack_add_named(stack, welcome_page(), "welcome");
    gtk_stack_add_named(stack, login_page(), "login");
    gtk_stack_add_named(stack, signup_page(), "signup"); 
    gtk_stack_add_named(stack, Withdrawl(), "withdrawl");
    gtk_stack_add_named(stack, home_page(), "homepage");

   
   

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
