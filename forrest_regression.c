#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct dataset{
    double data[100][5];
    int rows;
    int cols;    
};


struct dataset import_data(char* path){
        FILE *filepointer;
        struct dataset structure;
        char catchr[100];
        int row_itter = 0;
        int col_itter = 0;

        filepointer = fopen(path,"r");
        if (filepointer == NULL){
            perror("Error opening file");
            
        }

        while(fgets(catchr, sizeof(catchr), filepointer)){
            char *tok = strtok(catchr,",");
            //printf("%s,%s", tok,"\n");
            while (tok != NULL){
                structure.data[row_itter][col_itter] = atof(tok);
                col_itter += 1;
                tok = strtok(NULL,",");
                //printf("%s,%s", tok,"\n");
                
            }
            row_itter += 1;
            col_itter = 0;
        } 

        structure.rows = 100;
        structure.cols = 5;

        return structure;

};


struct training_example { 
    double distance;
    int index;
};


struct training_example_container{
    struct training_example* training_eg; 
    int size;       
};

void initialise_training_example_container(struct training_example_container *container, int size){
    container->training_eg = (struct training_example*)malloc(sizeof(struct training_example*) * size);
};


void free_memory_tec(struct training_example_container *ptr){
    free(ptr->training_eg);
};

int compare_distance(const void *a, const void *b) {
    const struct training_example *exampleA = (const struct training_example *)a;
    const struct training_example *exampleB = (const struct training_example *)b;

    if (exampleA->distance < exampleB->distance) {
        return -1; // A comes before B
    } else if (exampleA->distance > exampleB->distance) {
        return 1;  // B comes before A
    } else {
        return 0;  // Distances are equal
    }
}


int predict_for_examples(struct dataset d){
        
    int k = 4;
    int example_ind = 0;
    int k_start;
    int k_end;
    
    //find k nearest neighbors
    //printf("here:\n");
    
    for (example_ind; example_ind < d.rows; example_ind++){ //for each training example. 
        
        if (example_ind - k >= 0){
            k_start = example_ind - k;
        } else {
            k_start = 0;
        } 

        if (example_ind + k >= d.rows){
            k_end = d.rows - 1;
        } else {
            k_end = example_ind + k;
        }                                                   //set the start and begin indexes. 

        struct training_example_container tec;
        initialise_training_example_container(&tec,k);
        int container_itter = 0;
        int k_start_og = k_start; 
        tec.size = 0;

        for (k_start; k_start < k_end; k_start++){          //for each value calculate distance from training example and neighbors
            if (k_start != example_ind){
                struct training_example *eg;
                double distance = d.data[example_ind][4] - d.data[k_start][4];
                if (distance < 0){
                    distance *= -1;
                } 
                
                eg = &tec.training_eg[container_itter];    
                eg->distance = distance;             
                eg->index = k_start;
                //printf("%f,%s", tec.training_eg[container_itter].distance,"\n");
                tec.size++;
                
                                                            //save these values.        
                container_itter += 1; 

            }
        }

        //printf("tec.size = %d,%s",tec.size,"\n");

        //check if values saved correctly in the container.
        for (int itt = 0; itt < tec.size; itt++){
            //printf("Distance between chosen: %f,%s,%f,%s,%f,%s",d.data[example_ind][4]," and compare: ", d.data[k_start_og+1+itt][4], " = ", tec.training_eg[itt].distance,"\n\n");
            {};
        }
        
        //use q_sort
        qsort(tec.training_eg, tec.size, sizeof(struct training_example), compare_distance);
        double y_predict = 0.0;

        for (int itt = 0; itt < k; itt++){
            //printf("%d,%s",tec.training_eg[itt].index,"\n");
            y_predict += d.data[tec.training_eg[itt].index][4];
        } y_predict /= k;

        printf("prediction for example: %d,%s,%f,%s,%f,%s", example_ind, " = ", y_predict, " actual = ", d.data[example_ind][4],"\n"); 

        

        free_memory_tec(&tec);


    }


}



double test_accuracy(){
    return 1.1;
}


int main(){
    char* path = "final_dataset.csv";
    struct dataset my_data = import_data(path);
    printf("data[0][0] = %f", my_data.data[0][4]);
    int ideal_k = predict_for_examples(my_data);
    
    //double accuracy = accuracy(struct dataset d,ideal_k);
    //printf("accuracy using forrest regression: ", accuracy);
    //printf("%s",path);


    return 0;
}
















/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct dataset{
    double data[100][5];
    int rows;
    int cols;    
};


struct dataset import_data(char* path){
        FILE *filepointer;
        struct dataset structure;
        char catchr[100];
        int row_itter = 0;
        int col_itter = 0;

        filepointer = fopen(path,"r");
        if (filepointer == NULL){
            perror("Error opening file");
            
        }

        while(fgets(catchr, sizeof(catchr), filepointer)){
            char *tok = strtok(catchr,",");
            //printf("%s,%s", tok,"\n");
            while (tok != NULL){
                structure.data[row_itter][col_itter] = atof(tok);
                col_itter += 1;
                tok = strtok(NULL,",");
                //printf("%s,%s", tok,"\n");
                
            }
            row_itter += 1;
            col_itter = 0;
        } 

        structure.rows = 100;
        structure.cols = 5;

        return structure;

};


struct training_example { 
    double distance;
    int index;
};


struct training_example_container{
    struct training_example* training_eg; 
    int size;       
};

void initialise_training_example_container(struct training_example_container *container, int size){
    container->training_eg = (struct training_example*)malloc(sizeof(struct training_example*) * size);
};


void free_memory_tec(struct training_example_container *ptr){
    free(ptr->training_eg);
};

int compare_distance(const void *a, const void *b) {
    const struct training_example *exampleA = (const struct training_example *)a;
    const struct training_example *exampleB = (const struct training_example *)b;

    if (exampleA->distance < exampleB->distance) {
        return -1; // A comes before B
    } else if (exampleA->distance > exampleB->distance) {
        return 1;  // B comes before A
    } else {
        return 0;  // Distances are equal
    }
}




int findSmallestIndex(double arr[], int size) {

    int smallestIndex = 0;  // Initialize the index of the smallest value to the first element

    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[smallestIndex]) {
            smallestIndex = i;  // Update the index if a smaller value is found
        }
    }

    return smallestIndex;
}



int train(struct dataset d){
        
    int k = 10;
    int min_k = 3; 
    int example_ind = 0;
    int k_start;
    int k_end;
    int k_container[100];
    
    //find k nearest neighbors
    printf("here:\n");
    
    for (example_ind; example_ind < d.rows; example_ind++){ //for each training example. 
        double y_pred_container[8];
        for (int init_k = 3; init_k <= k; init_k++){                                                    //for each choice of k.
                        
            if (example_ind - init_k >= 0){
                k_start = example_ind - init_k;
            } else {
                k_start = 0;
            } 

            if (example_ind + init_k >= d.rows){
                k_end = d.rows - 1;
            } else {
                k_end = example_ind + init_k;
            }                                                   //set the start and begin indexes. 

            struct training_example_container tec;
            initialise_training_example_container(&tec,init_k);
            int container_itter = 0;
            int k_start_og = k_start; 
            tec.size = 0;

            for (k_start; k_start < k_end; k_start++){          //for each value calculate distance from training example and neighbors
                if (k_start != example_ind){
                    struct training_example *eg;
                    double distance = d.data[example_ind][4] - d.data[k_start][4];
                    if (distance < 0){
                        distance *= -1;
                    } 
                    
                    eg = &tec.training_eg[container_itter];    
                    eg->distance = distance;             
                    eg->index = k_start;
                    printf("%f,%s", tec.training_eg[container_itter].distance,"\n");
                    tec.size++;            
                                
                                                                                    
                    container_itter += 1; 

                }
            }

            printf("tec.size = %d,%s",tec.size,"\n");

            //check if values saved correctly in the container.
            for (int itt = 0; itt < tec.size; itt++){
                printf("Distance between chosen: %f,%s,%f,%s,%f,%s",d.data[example_ind][4]," and compare: ", d.data[k_start_og+1+itt][4], " = ", tec.training_eg[itt].distance,"\n\n");
            }
            
            //sort the structure.
            qsort(tec.training_eg, tec.size, sizeof(struct training_example), compare_distance);
            for (int itt = 0; itt < tec.size; itt++){
                printf("%d,%s",tec.training_eg[itt].distance,"\n");
            }

            //calculate y_predict using forrest regression.
            printf("predict");
            double y_predict = 0.0;
            for (int ind = 0; ind < tec.size; ind++){
                y_predict += d.data[ind][4];
            } y_predict /= tec.size;


            //store y_pred
            printf("predict");
            y_pred_container[init_k-min_k] = y_predict;
            free_memory_tec(&tec);

        }

        int best_k = findSmallestIndex(y_pred_container,8) + 3;
        printf("%dbest k = ", best_k);
    }

    


    double actual_y = d.data[example_ind][4];

    
    return 0;

}



double test_accuracy(){
    return 1.1;
}


int main(){
    char* path = "final_dataset.csv";
    struct dataset my_data = import_data(path);
    printf("data[0][0] = %f", my_data.data[0][4]);
    int ideal_k = train(my_data);
    
    //double accuracy = accuracy(struct dataset d,ideal_k);
    //printf("accuracy using forrest regression: ", accuracy);
    //printf("%s",path);


    return 0;
}*/