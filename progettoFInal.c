#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 10000

//STRUTTURE DATI

struct Veicolo{
    int key;
    struct Veicolo *v_left;
    struct Veicolo *v_right;
    struct Veicolo *v_padre;
};

struct Veicolo_list{
    struct Veicolo *veicolo_root;
    int max_veic;
};

struct Stazione{
    int key;
    struct Stazione *s_left;
    struct Stazione *s_right;
    struct Stazione *s_padre;
    struct Veicolo_list *veicoli_list;
};

struct Stazione_tree{
    struct Stazione *root_station;
};



//FUNZIONI VEICOLI
struct Veicolo *create_veicol_node(int key) {
    struct Veicolo* new_veicolo = malloc(sizeof(struct Veicolo));
    new_veicolo->key = key;
    new_veicolo->v_padre = NULL;
    new_veicolo->v_left = NULL;
    new_veicolo->v_right = NULL;
    return new_veicolo;
}

struct Veicolo *veicoloSearch(struct Veicolo *x, int k){
    if (x == NULL || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return veicoloSearch(x->v_left, k);
    } else {
        return veicoloSearch(x->v_right, k);
    }
}



void Veicolo_insert(struct Veicolo_list *root, struct Veicolo* z) {
    if(root!= NULL && z!= NULL){
        struct Veicolo *y = NULL;
        struct Veicolo *x = root->veicolo_root;

        if(x!=NULL){
            y = x;
            while (x != NULL) {
                y = x;
                if (z->key < x->key)
                    x = x->v_left;
                else
                    x = x->v_right;
            }
        }

        z->v_padre = y;
        if (y == NULL) {
            // L'albero è vuoto
            root->veicolo_root = z;
        } else if (z->key < y->key) {
            y->v_left = z;
        } else {
            y->v_right = z;
        }
    }

}


struct Veicolo *maximun_veicolo(struct Veicolo *s){
    if(s != NULL){
        while (s->v_right != NULL) {
            s = s->v_right;
        }
    }
    return s;
}

struct Veicolo *minimun_veicolo(struct Veicolo *s){
    while(s->v_left != NULL){
        s = s->v_left;
    }
    return s;
}

struct Veicolo *tree_successor_veicolo(struct Veicolo *s){
    if(s->v_right != NULL){
        return minimun_veicolo(s->v_right);
    }
    struct Veicolo* y = NULL;
    y = s->v_padre;
    while(y != NULL && s == y->v_right){
        s = y;
        y = y->v_padre;
    }
    return y;
}

struct Veicolo *Veicolo_delete(struct Veicolo_list *root, struct Veicolo *z){
    struct Veicolo* y = NULL, *x = NULL;
    if(z->v_left == NULL || z->v_right == NULL){
        y = z;
    } else{
        y = tree_successor_veicolo(z);
    }

    if(y->v_left != NULL){
        x = y->v_left;
    } else{
        x = y->v_right;
    }

    if(x != NULL){
        x->v_padre = y ->v_padre;
    }

    if(y->v_padre == NULL){
        root->veicolo_root = x;
    } else if(y == y->v_padre->v_left){
        y->v_padre->v_left = x;
    } else {
        y->v_padre->v_right = x;
    }

    if(y != z){
        z->key = y->key;
    }

    return y;  // returna il nodo da cancellare
}


void postOrderTreeWalk_delete(struct Veicolo *s){

    if(s != NULL){
        postOrderTreeWalk_delete(s->v_left);
        postOrderTreeWalk_delete(s->v_right);
        s->v_right=NULL;
        s->v_left=NULL;
        s->v_padre = NULL;
        free(s);
        s= NULL;

    }
}

void deleteAllAuto(struct Veicolo_list *list){
    if(list != NULL && list->veicolo_root != NULL){
        postOrderTreeWalk_delete(list->veicolo_root);
        list->veicolo_root = NULL;
    }
    free(list);
}



void inOrderTreeWalkCountVeicol(struct Veicolo *v, struct Veicolo_list *new){
    if(v!=NULL) {
        inOrderTreeWalkCountVeicol(v->v_left, new);
        inOrderTreeWalkCountVeicol(v->v_right, new);
        Veicolo_insert(new, create_veicol_node(v->key));
    }
}


//FUNZIONI STAZIONI
struct Stazione *create_station_node(int key) {
    struct Stazione* new_station = malloc(sizeof(struct Stazione));
    new_station->key = key;
    new_station->s_padre = NULL;
    new_station->s_left = NULL;
    new_station->s_right = NULL;
    new_station->veicoli_list = NULL;
    return new_station;
}


struct Stazione *treeSearch(struct Stazione *x, int k){
    if (x == NULL || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return treeSearch(x->s_left, k);
    } else {
        return treeSearch(x->s_right, k);
    }
}


void Station_insert(struct Stazione_tree *root, struct Stazione* z) {
    struct Stazione* y = NULL;
    struct Stazione* x = root->root_station;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->s_left;
        else
            x = x->s_right;
    }

    z->s_padre = y;
    if (y == NULL) {
        // L'albero è vuoto
        root->root_station = z;
    } else if (z->key < y->key) {
        y->s_left = z;
    } else {
        y->s_right = z;
    }

}


struct Stazione *minimun(struct Stazione *s){
    while(s->s_left != NULL){
        s = s->s_left;
    }
    return s;
}


struct Stazione *tree_successor(struct Stazione *s){
    if(s->s_right != NULL){
        return minimun(s->s_right);
    }
    struct Stazione* y = NULL;
    y = s->s_padre;
    while(y != NULL && s == y->s_right){
        s = y;
        y = y->s_padre;
    }
    return y;
}

struct Stazione *Station_delete(struct Stazione_tree *root, struct Stazione *z){
    struct Stazione* y = NULL, *x = NULL;
    if(z->s_left == NULL || z->s_right == NULL){
        y = z;
    } else{
        y = tree_successor(z);
    }

    if(y->s_left != NULL){
        x = y->s_left;
    } else{
        x = y->s_right;
    }

    if(x != NULL){
        x->s_padre = y ->s_padre;
    }

    if(y->s_padre == NULL){
        root->root_station = x;
    } else if(y == y->s_padre->s_left){
        y->s_padre->s_left = x;
    } else {
        y->s_padre->s_right = x;
    }

    if(y != z){
        z->key = y->key;
        deleteAllAuto(z->veicoli_list);
        z->veicoli_list = malloc(sizeof (struct Veicolo_list));
        z->veicoli_list->veicolo_root = NULL;
        inOrderTreeWalkCountVeicol(y->veicoli_list->veicolo_root, z->veicoli_list);
        z->veicoli_list->max_veic = maximun_veicolo(z->veicoli_list->veicolo_root)->key;
    }

    return y;  // returna il nodo da cancellare
}

int inOrderTreeWalk_count(struct Stazione *s, int start, int end, int count) {
    if (s != NULL) {
        count = inOrderTreeWalk_count(s->s_left, start, end, count);
        if (s->key >= start && s->key <= end) {
            count++;
        }
        if (s->key <= end) {  // Interrompi la ricorsione se superi l'elemento massimo dell'intervallo
            count = inOrderTreeWalk_count(s->s_right, start, end, count);
        }
    }
    return count;
}

int reverseOrderWalk(struct Stazione *s, int start, int end, int count){
    if(s != NULL){
        count = reverseOrderWalk(s->s_right,start, end, count);
        if (s->key <= start && s->key >= end){
            count++;
        }
        if(s->key >= end){
            count = reverseOrderWalk(s->s_left, start, end, count);
        }
    }
    return count;
}




//FUNZIONI PIANIFICA PERCORSO

struct Stazione_array{
    int key;
    int maxAutonomia;
    int visited;
    int predKey;
    int predIndex;
    int dist;
};


void inOrderTreeWalkArrayCreation(struct Stazione *s, int start, int end, struct Stazione_array *array, int *count) {
    if (s != NULL) {
        inOrderTreeWalkArrayCreation(s->s_left, start, end, array, count);
        if (s->key >= start && s->key <= end) {
            //printf(" %d ", s->key);
            array[*count].key = s->key;
            array[*count].maxAutonomia = 0;
            array[*count].predKey = -1;
            array[*count].predIndex = -1;
            array[*count].visited = 0;
            if(s->veicoli_list!=NULL){
                array[*count].maxAutonomia = s->veicoli_list->max_veic;
            }


            (*count)++;
        }
        if (s->key <= end) {  // Interrompi la ricorsione se superi l'elemento massimo dell'intervallo
            inOrderTreeWalkArrayCreation(s->s_right, start, end, array, count);
        }
    }
}

void ReverseOrderTreeWalkArrayCreation(struct Stazione *s, int start, int end, struct Stazione_array *array, int *count) {
    if (s != NULL) {
        ReverseOrderTreeWalkArrayCreation(s->s_right, start, end, array, count);
        if (s->key <= start && s->key >= end) {
            array[*count].key = s->key;
            array[*count].maxAutonomia = 0;
            array[*count].predKey = -1;
            array[*count].predIndex = -1;
            array[*count].visited = 0;
            array[*count].dist = 1000000;
            if(s->veicoli_list!=NULL){
                array[*count].maxAutonomia = s->veicoli_list->max_veic;
            }
            (*count)++;
        }
        if (s->key >= end) {
            ReverseOrderTreeWalkArrayCreation(s->s_left, start, end, array, count);
        }
    }
}

void findMinPath(struct Stazione_array stations[], int NumStations, int path[], int *pathlenght){
    int boolean = 0;

    for(int i = 0; i< NumStations; i++){
        //printf(" i = %d")
        int j = i+1;

        while (stations[j].key - stations[i].key <= stations[i].maxAutonomia){
            if(stations[j].visited == 0){
                stations[j].visited = 1;
                stations[j].predKey = stations[i].key;
                stations[j].predIndex = i;

            }
            if( j == NumStations - 1){
                boolean = 1;
                break;
            }
            j++;

        }
        if(i == j-1 && stations[i+1].visited == 0){
            break;
        }

        if(boolean == 1){
            break;
        }
    }

    int h = NumStations-1;
    path[0] = stations[NumStations-1].key;
    (*pathlenght)++;
    while(h != 0){
        path[*pathlenght] = stations[h].predKey;
        (*pathlenght)++;
        if(stations[h].predIndex != -1){
            h = stations[h].predIndex;
        } else {
            break;
        }
    }
}


void findMinPathReversal (struct Stazione_array stations[], int NumStations, int path[], int *pathlength){
    int i = 0, currDist = 1, booleanEnd = 0;

    while(i < NumStations){
        int j = i+1;

        while(stations[i].key - stations[j].key <= stations[i].maxAutonomia && j < NumStations){
            if(stations[j].visited == 0){
                stations[j].predKey = stations[i].key;
                stations[j].visited = 1;
                stations[j].predIndex = i;
                stations[j].dist = stations[i].dist+1;
            }

            if(j == NumStations-1){
                booleanEnd = 1;
                break;
            }
            j++;

        }

        if(j==1){
            break;
        }

        if(booleanEnd == 1){
            break;
        }

        if(i == 0){
            i = j-1;
            currDist++;
        } else if(stations[i].dist == stations[i-1].dist){
            i--;
        } else{

            if(stations[i].dist == currDist-1){
                while (stations[i].dist <= currDist && i < NumStations - 1) {
                    i++;
                }
                i--;
                currDist++;
            } else {
                booleanEnd = 1;
            }
        }
    }

    int h = NumStations-1;
    path[0] = stations[NumStations-1].key;
    (*pathlength)++;
    while(h != 0){
        path[*pathlength] = stations[h].predKey;
        (*pathlength)++;
        if(stations[h].predIndex != -1){
            h = stations[h].predIndex;
        } else {
            break;
        }
    }
}

void createStationsArray(struct Stazione *s, int start, int end, struct Stazione_array *array){


    int arrayLength = 0;
    if(start < end){
        inOrderTreeWalkArrayCreation(s, start, end, array, &arrayLength);
    } else{
        ReverseOrderTreeWalkArrayCreation(s, start, end, array, &arrayLength);
    }
}



//FUNZIONI DEI COMANDI
void aggiungiStazione(int arr[], int length, struct Stazione_tree *list){
    struct Stazione *new_station = NULL, *temp = NULL;

    temp = treeSearch(list->root_station, arr[0]);

    if(temp != NULL){
        printf("non aggiunta\n");
    } else {

        new_station = create_station_node(arr[0]);

        struct Veicolo_list *new_veicolo_list = NULL;
        struct Veicolo *tempVeic = NULL;
        new_veicolo_list = malloc(sizeof(struct Veicolo_list));
        new_veicolo_list->max_veic = 0;
        new_veicolo_list->veicolo_root = NULL;
        new_station->veicoli_list = new_veicolo_list;
        for (int i = 2; i < length; i++) {
            Veicolo_insert(new_veicolo_list, create_veicol_node(arr[i]));
        }
        tempVeic = maximun_veicolo(new_veicolo_list->veicolo_root);
        if(tempVeic != NULL){
            new_station->veicoli_list->max_veic = tempVeic->key;
        }

        Station_insert(list, new_station);
        printf("aggiunta\n");
    }
}

void rimuoviStazione(int distanza, struct Stazione_tree *list){
    if(list != NULL){

        struct Stazione *temp, *delete_temp;
        temp = treeSearch(list->root_station, distanza);
        if (temp != NULL) {
            delete_temp = Station_delete(list, temp);
            deleteAllAuto(delete_temp->veicoli_list);
            delete_temp->veicoli_list = NULL;
            free(delete_temp);
            printf("demolita\n");
        } else {
            printf("non demolita\n");
        }
    }
}

void aggiungiVeicolo(int distanza, int autonomia, struct Stazione_tree *list){
    struct Stazione *temp;
    temp = treeSearch(list->root_station, distanza);

    if(temp != NULL){
        if(temp->veicoli_list == NULL){
            temp->veicoli_list = malloc(sizeof (struct Veicolo_list));
            temp->veicoli_list->veicolo_root = NULL;
            temp->veicoli_list->max_veic = 0;
        }
        if(temp->veicoli_list!= NULL && autonomia > temp->veicoli_list->max_veic){
            temp->veicoli_list->max_veic = autonomia;
        }
        Veicolo_insert(temp->veicoli_list, create_veicol_node(autonomia));
        printf("aggiunta\n");
    }
    else {
        printf("non aggiunta\n");
    }


}

void rottamaVeicolo(int distanza, int autonomia, struct Stazione_tree *list){
    struct Stazione *temp;
    temp = treeSearch(list->root_station, distanza);

    //cerco che la stazione esista
    if(temp != NULL){
        struct Veicolo *delete_temp, *veicolo_temp;

        if(temp->veicoli_list != NULL) {
            veicolo_temp = veicoloSearch(temp->veicoli_list->veicolo_root, autonomia);

            if (veicolo_temp != NULL) {
                delete_temp = Veicolo_delete(temp->veicoli_list, veicolo_temp);
                delete_temp->v_right = NULL;
                delete_temp->v_left = NULL;
                delete_temp->v_padre = NULL;
                free(delete_temp);

                if (autonomia == temp->veicoli_list->max_veic) {
                    if(temp->veicoli_list->veicolo_root == NULL){
                        temp->veicoli_list->max_veic = 0;
                    } else {
                        temp->veicoli_list->max_veic = maximun_veicolo(temp->veicoli_list->veicolo_root)->key;
                    }
                }
                printf("rottamata\n");
            } else {
                printf("non rottamata\n");
            }

        } else{
            printf("non rottamata\n");
        }

    } else {
        printf("non rottamata\n");
    }


}

void pianificaPercorso(int start, int end, struct Stazione_tree *tree){
    //controllo che start e end esistano
    struct Stazione *temp;
    temp = treeSearch(tree->root_station, start);
    if(temp == NULL){
        printf("nessun percorso\n");
        return;
    }
    temp = treeSearch(tree->root_station, end);
    if(temp == NULL){
        printf("nessun percorso\n");
        return;
    }

    if(start == end){
        printf("%d\n", start);
        return;
    }

    int count = 0;

    if(start < end) {
        count = inOrderTreeWalk_count(tree->root_station, start, end, 0);
    }else {
        count = reverseOrderWalk(tree->root_station, start, end, 0);
    }
    struct Stazione_array *array = NULL;
    array = malloc(count * sizeof (struct Stazione_array));

    createStationsArray(tree->root_station, start, end, array);

    array[0].dist = 0;

    int *path = malloc(count * sizeof(int));
    int pathLength = 0;
    if(start < end){
        findMinPath(array, count, path, &pathLength);
    } else{
        findMinPathReversal(array, count, path, &pathLength);
    }



    if (pathLength > 0 && path[0] == array[count-1].key && path[pathLength-1] == array[0].key) {
        for (int i = pathLength-1; i > 0 ; i--) {
            printf("%d ", path[i]);
        }
        printf("%d", path[0]);
        printf("\n");
    } else {
        printf("nessun percorso\n");
    }

    free(array);
    free(path);

}

void postOrderDeleteStations(struct Stazione *s){
    if(s != NULL){
        postOrderDeleteStations(s->s_left);
        postOrderDeleteStations(s->s_right);
        deleteAllAuto(s->veicoli_list);
        s->veicoli_list = NULL;
        s->s_left = NULL;
        s->s_right = NULL;
        s->s_padre = NULL;
        free(s);
        s = NULL;
    }
}

void DeleteAll(struct Stazione_tree *tree){
    if(tree != NULL && tree->root_station != NULL){
        postOrderDeleteStations(tree->root_station);
    }
    tree->root_station = NULL;
}


//MAIN
int main( ){

    struct Stazione_tree *Station_Top = malloc(sizeof (struct Stazione_tree));
    Station_Top->root_station = NULL;
    char inputline[LINE_LENGTH];

    // Leggiamo fino alla fine
    while (fgets(inputline, LINE_LENGTH, stdin) != NULL) {

        //caso aggiungi staz
        if(inputline[0] == 'a' && inputline[9] == 's'){

            int inputArray[514] = {0}; //inizializza tutti gli elementi a 0

            int i = 18, j = 0, array_index = 0, num = 0;
            char station[20] = "a";

            while (inputline[i] != '\0'){
                if(inputline[i] != ' '){
                    station[j] = inputline[i];
                    j++;
                    i++;
                } else {
                    station[j] ='\0';
                    num = atoi(station);
                    inputArray[array_index] = num;
                    j = 0;
                    i++;
                    array_index++;

                }
            }

            if(j > 0){
                station[j] = '\0';
                num = atoi(station);
                inputArray[array_index] = num;
            }

            int length = 0;
            if(array_index > 1){
                length = inputArray[1];
            }

            aggiungiStazione(inputArray, length+2, Station_Top);


        }

        else if(inputline[0] == 'd' && inputline[10] == 's'){
            int i = 19, j = 0;
            char station[20] = "a";
            while(inputline[i] != '\0'){
                station[j] = inputline[i];
                i++;
                j++;
            }
            station[j] = '\0';


            int station_key = atoi(station);


            rimuoviStazione(station_key, Station_Top);
        }

        else if(inputline[0] == 'a' && inputline[9] == 'a'){
            int i = 14, j = 0;
            char station[20] = "a";
            char veicolo[20] = "a";
            while (inputline[i] != ' '){
                station[j] = inputline[i];
                j++;
                i++;
            }
            j = 0;
            while (inputline[i] != '\0'){
                veicolo[j] = inputline[i];
                j++;
                i++;
            }

            int station_key = 0, veicolo_key= 0;
            station_key = atoi(station);
            veicolo_key = atoi(veicolo);


            aggiungiVeicolo(station_key, veicolo_key, Station_Top);

        }

            //caso rimuovi auto
        else if(inputline[0] == 'r' && inputline[8] == 'a'){
            int i = 13, j = 0;
            char station[20] = "a";
            char veicolo[20] = "a";
            while (inputline[i] != ' '){
                station[j] = inputline[i];
                j++;
                i++;
            }
            j = 0;
            while (inputline[i] != '\0'){
                veicolo[j] = inputline[i];
                j++;
                i++;
            }
            int station_key, veicolo_key;
            station_key = atoi(station);
            veicolo_key = atoi(veicolo);


            rottamaVeicolo(station_key, veicolo_key, Station_Top);
        }


        else{

            int i = 19, j = 0;
            char station_initial[20] = "a";
            char station_final[20] = "a";
            while (inputline[i] != ' '){
                station_initial[j] = inputline[i];
                j++;
                i++;
            }
            j = 0;
            while (inputline[i] != '\0'){
                station_final[j] = inputline[i];
                j++;
                i++;
            }
            int station_key_initial, station_key_final;
            station_key_initial = atoi(station_initial);
            station_key_final = atoi(station_final);


            pianificaPercorso(station_key_initial, station_key_final, Station_Top);

        }

    }

    DeleteAll(Station_Top);
    if(Station_Top != NULL){
        free(Station_Top);
    }

    return 0;
}
