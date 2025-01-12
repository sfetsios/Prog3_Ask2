#include "e_shop.h"

// Sunartisi arxikopoiisis twn antikimenon Katastima
void ftiakse_katastima(Katastima *katastima) {
    const char *base_names[20] = {
        "Laptop", "Mouse","Keyboard", "Monitor","Headphones", 
        "Tablet", "Printer", "Camera", "Smartphone", "Router", 
        "Speakers","Webcam","Microphone", "ExternalDrive","USBHub", 
        "Charger", "Projector","Smartwatch","TV", "GameConsole"};
    
    
    for (int i = 0; i < 20; i++) {
        // arxikopoiisi periexomenwn antikeimenwn
        strcpy(katastima->antikeimeno[i].description, base_names[i]);
        katastima->antikeimeno[i].posotita = 2; // arxikopoiisi posotitas antikeimenou me 2
        katastima->antikeimeno[i].timi = ((rand() % 100) + 1) * 1; } // arxikopoiisi timis antikeimenou apo 1-100

    // arxikopoiisi twn upoloipwn stoixeiwn tou struct katastima
    katastima->esoda = 0.0;
    katastima->olokl_parag = 0;
    katastima->apotux_parag = 0;

}

// Paraggelia gia th thugatriki diergasia
int process_order(Katastima *katastima, parag *order) {
    for (int i = 0; i < 20; i++) {
        // Elegxos an to antikeimeno uparxei ston katastima 
        if (strcmp(katastima->antikeimeno[i].description, order->item_name) == 0) {
            // To vrikame
            katastima->antikeimeno[i].total_orders++; // Auksanoume tis sunolikes paraggelies
            if (katastima->antikeimeno[i].posotita >= order->posotita) {
                katastima->antikeimeno[i].posotita -= order->posotita;
                 katastima->antikeimeno[i].poliseis += order->posotita;  // Auksanoume tis paraggelies gia auto to antikeimeno
                 katastima->esoda += katastima->antikeimeno[i].timi * order->posotita;
                katastima->olokl_parag++;
                return katastima->antikeimeno[i].timi * order->posotita;  // Epituxia
            } else {
                // Den uparxei alla diathesima
                 katastima->posotita[i].apotux_parag++;  // Auksanoume tis apotuximenes paraggelies
                katastima->apotux_parag++;
                return -1;  // Apotuxia logo apothematos
            }
        }
    }
    // An den uparxei to antikeimeno ston katastima
    katastima->apotux_parag++;
    return -1;  // Apotuxia 
}

int main (void){
    // Dimiourgia struct EKATASTIMA
    Katastima EKATASTIMA; 
    // Giaa na exoume tuxaies times
    srand(time(NULL));  
    
    // Kalw th sunartisi gia to struct EKATASTIMA
    ftiakse_katastima(&EKATASTIMA); 

    // Diaulos epikoinonias
    int pipefd[2];

    // arxikopoiisi metavlitis pid
    pid_t pid ; 
    // arxikopoiisi buffer
    char buffer[BUFFER_SIZE]; 

    // Dimiourgia pipes
    if (pipe(pipefd) ==-1) {
        // periptosi sfalmatos
        perror("Pipe apetixe!!");
        exit(EXIT_FAILURE);}
    //Sunexeia
    for (int client_id = 1; client_id <= 5; client_id++) {

        pid = fork();

        if (pid < 0) {
            // Apotuxia ektelisis fork
            perror("Fork() apetixe!!");
            exit(EXIT_FAILURE);

        } else if (pid == 0) {  
            // Diergasia paidi
            close(pipefd[0]);  // kleinoume pipes anagnwsis
            // Copy struct katastima gia tis diergasies paidia
            antikeimeno local_shop[20];
            
            memcpy(local_shop, EKATASTIMA);
            //10 paraggelies gia kathe diergasia paidi
            for (int j = 0; j < 10; j++) {
                //antikeimeno parag 
                parag order;
                 int random_item_index = rand() % 20;  // Tuxaia epilogi antikeimenou
                strcpy(order.item_name, local_shop[random_item_index].description);  // Antigrafi onomatos local
                // Paraggelia 1 antikeimeno
                order.posotita = 1;  
                // Grapsimo ston pipe
                if (write(pipefd[1], &order, sizeof(parag)) == -1) {
                    // Apotuxia grapsimatos ston pipe
                    perror("Error writing to pipe");
                    exit(EXIT_FAILURE);
                }

            }
            close(pipefd[1]);  // kleinoume pipes grapsimatos
            exit(EXIT_SUCCESS);
        }
    }
        
    // Exoume 50 paraggelies, ektelesi kwdika patrikis diergasias
    for (int i = 0; i < 50; i++) {  

        parag order;
        // anagnwsi apo to pipe ths paraggelias
        read(pipefd[0], &order, sizeof(parag));
        // Kalesma sunartisis gia thn paraggelia
        int timi = process_order(&EKATASTIMA,&order); 
        if (timi > 0) {
            printf("Pelatis %d: parag Epituxis gia %s x%d. Sunoliko kostos: $%.2f\n", i, order.item_name, order.posotita, (float)timi);
        } else {
            printf("Pelatis %d: parag Apetuxe gia %s x%d.\n", i , order.item_name, order.posotita);
        }
    }

    close(pipefd[0]);  // Kleisimo pipes anagnwsis

     // perimenoume na teleiwsoun oi thugatrikes diergasies tin ektelesh tous
    for (int i = 0; i < 5; i++) {
        wait(NULL); 
    }

    // Teliko print gia to katastima
    printf("\nTziros Katastima :\n");
    printf("Total Earnings: $%.2f\n", EKATASTIMA.esoda);  
    printf("Successful Orders: %d\n", EKATASTIMA.olokl_parag); 
    printf("Declined Orders: %d\n", EKATASTIMA.apotux_parag); 

    // Statistika antikeimenwn tou katastimatos
    printf("\n Statistika Antikeimenwn: \n");
    for (int i = 0; i < 20; i++) {
        printf("%s: Sunolikes paraggelies = %d, Sold = %d, Unsuccessful Orders = %d\n", 
               EKATASTIMA.antikeimeno[i].description,EKATASTIMA.antikeimeno[i].total_orders,EKATASTIMA.antikeimeno[i].poliseis,EKATASTIMA.antikeimeno[i].apotux_parag); // Dimiourgia struct katastima.posotita[i].description, EKATASTIMA; // Dimiourgia struct katastima.posotita[i].total_orders, EKATASTIMA; // Dimiourgia struct katastima.posotita[i].poliseis, EKATASTIMA; // Dimiourgia struct katastima.posotita[i].apotux_parag);
    }
    //Telos programmatos
    return 0;
}