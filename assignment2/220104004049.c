#include <stdio.h>

int main() {
    FILE *data = fopen("data.txt","r");
    int x, y, label, testLabel;
    int errorCounter = 0;
    int minErrorCounter = 1000;
    int minSepX, minSepY; 
    int minR1, minR2, minR3, minR4;
    int tmp_errorCounter;
    int r1,r2,r3,r4;
    int deneme = 0;
    
    int x0min;
    int x0max = 0;
    int y0min;
    int y0max = 0;
    
    int x1min;
    int x1max = 0;
    int y1min;
    int y1max = 0;
    
    int sepX , sepY;
    int xMin, xMax, yMin, yMax;

    if (data == NULL)
    {
        printf("Error");
    }
    else
    {
        fscanf(data,"%d %d %d", &x, &y, &label);
        while ( label != 1 )
        {
            fscanf(data,"%d %d %d", &x, &y, &label);
        }
        x0min = x;
        y0min = y;
        while ( label != 0)
        {
            fscanf(data,"%d %d %d", &x, &y, &label);
        }
        x1min = x;
        y1min = y;
        fseek(data, 0, SEEK_SET);
        while (fscanf(data,"%d %d %d", &x, &y, &label) != EOF)
        {
            if (label == 0)
            {
                if (x > x0max)
                {
                    x0max = x;
                }
                if (x < x0min)
                {
                    x0min = x;
                }
                if (y > y0max)
                {
                    y0max = y;
                }
                if (y < y1min)
                {
                    y0min = y;
                }
            }
            else if (label == 1)
            {
                if (x > x1max)
                {
                    x1max = x;
                }
                if (x < x1min)
                {
                    x1min = x;
                }
                if (y > y1max)
                {
                    y1max = y;
                }
                if (y < y1min)
                {
                    y1min = y;
                }
            }
            else
            {
                printf("invalid label");
            }
        }
        
        /*
        printf("label 0 : x[%d,%d] y[%d,%d]\n",x0min,x0max,y0min,y0max);
        printf("label 1 : x[%d,%d] y[%d,%d]\n\n",x1min,x1max,y1min,y1max);
        */
    }
    fclose(data);
    
    if (y0min < y1min)
    {
        yMin = y0min;
    }
    else
    {
        yMin = y1min;
    }

    if (x0min < x1min)
    {
        xMin = x0min;
    }
    else
    {
        xMin = x1min;
    }

    if (y0max > y1max)
    {
        yMax = y0max;
    }
    else
    {
        yMax = y1max;
    }
    
    if (x0max > x1max)
    {
        xMax = x0max;
    }
    else
    {
        xMax = x1max;
    }
    /*
    printf("xMin : %d, xMax : %d\n",xMin,xMax);
    printf("yMin : %d, yMax : %d\n\n",yMin,yMax);
    */
    sepX = xMin;
    sepY = yMin;
    data = fopen("data.txt", "r");
    while (sepX <= xMax) {
        sepY = yMin;
        while (sepY <= yMax) {
            for (r1 = 0; r1 <= 1; r1++) {
                for (r2 = 0; r2 <= 1; r2++) {
                    for (r3 = 0; r3 <= 1; r3++) {
                        for (r4 = 0; r4 <= 1; r4++) {
                            tmp_errorCounter = 0;
                            fseek(data, 0, SEEK_SET);
                            while (fscanf(data, "%d %d %d", &x, &y, &label) != EOF) {
                                if (x <= sepX && y > sepY) {
                                    testLabel = r1;
                                    if (testLabel != label) {
                                        tmp_errorCounter++;
                                    }
                                } else if (x > sepX && y > sepY) {
                                    testLabel = r2;
                                    if (testLabel != label) {
                                        tmp_errorCounter++;
                                    }
                                } else if (x <= sepX && y <= sepY) {
                                    testLabel = r3;
                                    if (testLabel != label) {
                                        tmp_errorCounter++;
                                    }
                                } else if (x > sepX && y <= sepY) {
                                    testLabel = r4;
                                    if (testLabel != label) {
                                        tmp_errorCounter++;
                                    }
                                }
                            }
                           if (tmp_errorCounter < minErrorCounter) 
                           { 
                            minErrorCounter = tmp_errorCounter;
                            minSepX = sepX;
                            minSepY = sepY;
                            minR1 = r1;
                            minR2 = r2;
                            minR3 = r3;
                            minR4 = r4;
                            /*
                            printf("En düşük hata veren etiket kombinasyonu:\n");
                            printf("R1 = %d, R2 = %d, R3 = %d, R4 = %d\n", r1, r2, r3, r4);
                            printf("Separator coordinates: X = %d, Y = %d\n", sepX, sepY);
                            printf("Training error of the model = %d\n", tmp_errorCounter);
                            printf("--------------------------------------------\n");
                            */
                            deneme++;
                            break;
                            }               
                        }
                    }
                }
            }
            sepY++;
        }
        sepX++;
    }
    /*
    printf("En düşük hata veren etiket kombinasyonu:\n");
    printf("R1 = %d, R2 = %d, R3 = %d, R4 = %d\n", minR1, minR2, minR3, minR4);
    printf("Separator coordinates: X = %d, Y = %d\n", minSepX, minSepY);
    printf("Training error of the model = %d\n", minErrorCounter);
    printf("deneme : %d\n",deneme);
    printf("--------------------------------------------\n");
    */
    fclose(data);


    double success;
    double data_counter;
    double success_error;
    int tmp_label;
    data = fopen("test 1.txt","r");
    while (fscanf(data,"%d %d %d",&x,&y,&label) != EOF)
    {
        if (x <= minSepX && y < minSepY)
        {
            tmp_label = minR1;
            if (tmp_label != label)
            {
                success_error++;
            }
        }
        else if (x > minSepX && y > minSepY)
        {
            tmp_label = minR2;
            if (tmp_label != label)
            {
                success_error++;
            }
        }
         else if (x <= minSepX && y <= minSepY)
        {
            tmp_label = minR3;
            if (tmp_label != label)
            {
                success_error++;
            }
        }
         else if (x > minSepX && y <= minSepY)
        {
            tmp_label = minR4;
            if (tmp_label != label)
            {
                success_error++;
            }
        }
        data_counter++;
    }

    success = ((data_counter - success_error) / data_counter) * 100;
    /*printf("Success : %% %.2lf\n",success);*/
     fclose(data);

    char choice;
    int flag = 1;
    int flag2 = 0;
    printf("1. Explore Data : Implement functionality to read and display the data points from the data.txt file,\nallowing the user to explore the dataset.\n");
    printf("2. Train Model : Develop code to construct AI model using the data points read from the data.txt file.\nUse the algorithm implemented in Question 2.\n");
    printf("3. Test Model : Create functionality to read test data points from the test.txt file,\npredict their class labels using the trained AI model, and display the results.\n");
    printf("4. Exit : Provide an option for the user to exit the program.\n");
    while (flag)
    {
        printf("Choice : ");
        scanf(" %c",&choice);
        switch (choice)
            {
            case '1' :
                printf("label 0 : x[%d,%d] y[%d,%d]\n",x0min,x0max,y0min,y0max);
                printf("label 1 : x[%d,%d] y[%d,%d]\n\n",x1min,x1max,y1min,y1max);
                break;
            case '2' :
                printf("The tag combination with the lowest error:\n");
                printf("R1 = %d, R2 = %d, R3 = %d, R4 = %d\n", minR1, minR2, minR3, minR4);
                printf("Separator coordinates: X = %d, Y = %d\n", minSepX, minSepY);
                printf("Training error of the model = %d\n", minErrorCounter);
                printf("Number of attempts : %d\n",deneme);
                printf("--------------------------------------------\n");
                flag2 = 1;
                break;
            case '3' :
                if(flag2 == 1)
                {
                    printf("Success : %% %.2lf\n",success);
                    FILE *data2;
                    int lx,ly;
                    int tmp2_label;
                    data2 = fopen("test-final.txt","r");
                    while (fscanf(data2,"%d %d",&lx,&ly) != EOF)
                    {
                        if (lx <= minSepX && ly < minSepY)
                        {
                        tmp2_label = minR1;
                        }
                        else if (lx > minSepX && ly > minSepY)
                        {
                        tmp2_label = minR2;
                        }
                        else if (lx <= minSepX && ly <= minSepY)
                        {
                        tmp2_label = minR3;
                        }
                        else if (lx > minSepX && ly <= minSepY)
                        {
                        tmp2_label = minR4;
                        }
                        printf("x= %d y = %d label = %d\n",lx,ly,tmp2_label);
                    }
                    fclose(data2);
                }
                else
                {
                    printf("you can't test your model without training it !\n");
                }
                break;
            case '4':
                printf("Exiting...\n");
                flag = 0;
                break;    
            default:
                printf("invalid choice\n");
                break;
            }
    } 
    return 0;
}
