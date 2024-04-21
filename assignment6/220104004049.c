#include  <stdio.h>

void drawHistogram(int array[], int size, int values[], int lower_bound, int upper_bound)
{
    int max_frequency = 0;
    int value_count = 0;
    int value;
    int j, i;

    value = lower_bound;
    for (value = lower_bound; value <= upper_bound + 1; value++)
    {
        int i = 0;
        for (i = 0; i < size; i++)
        {
            if (values[i] == value)
            {
                value_count++;
            }
        }
        if (value_count > max_frequency)
        {
            max_frequency = value_count;
        }
        value_count = 0;
    }

    for (i = max_frequency; i > 0; i--)
    {
        for (j = lower_bound - 1; j < upper_bound; j++)
        {
            if (array[j] >= i)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void add_number(int array[], int num, int *size, int lower_bound, int upper_bound) 
{
  if ((num >= lower_bound) && (num <= upper_bound)) 
  {
    array[*size] = num;
    *size = *size + 1;
  }
}

float calculateAverage(int array[], int size, int lower_bound, int upper_bound) 
{
    int total = 0;
    int count = 0;
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (array[i] >= lower_bound && array[i] <= upper_bound)
        {
            total += array[i];
            count++;
        }
    }
    if (count == 0)
    {
        printf("Error");
    }
    return (float) total / count;
}

float calculateMedian(int array[], int size, int lower_bound, int upper_bound) {
    int i, j;
    int count = 0;
    for (i = 0; i < size; i++)
    {
        if (array[i] >= lower_bound && array[i] <= upper_bound)
        {
            count++;
        }
    } 
    int indices[count];
    int index = 0;
    for (i = 0; i < size; i++)
    {
        if (array[i] >= lower_bound && array[i] <= upper_bound)
        {
            indices[index++] = i;
        }
    }
    for (i = 0; i < count - 1; i++) 
    {
        int minIndex = i;
        for (j = i + 1; j < count; j++) 
        {
            if (array[indices[j]] < array[indices[minIndex]]) 
            {
                minIndex = j;
            }
        }
        int temp = indices[minIndex];
        indices[minIndex] = indices[i];
        indices[i] = temp;
    }
    if (count % 2 == 0)
     {
        int mid1 = indices[count / 2 - 1];
        int mid2 = indices[count / 2];
        return (array[mid1] + array[mid2]) / 2.0;
    } 
    else 
    {
        int mid = indices[count / 2];
        return array[mid];
    }
}

float calculateMode(int array[], int size, int lower_bound, int upper_bound) {
    int maxCount = 0;
    int mode = -1;
    int frequencies[250] = {0};
    int i; 
    for (i = 0; i < size; i++) 
    {
        if (array[i] >= lower_bound && array[i] <= upper_bound) 
        {
            frequencies[array[i] - 1]++;
        }
    }

    for (i = lower_bound - 1; i < upper_bound; i++) 
    {
        if (frequencies[i] > maxCount)
        {
            maxCount = frequencies[i];
            mode = i + 1; 
        }
    }

    return mode;
}

int find_size_of_array(int *arr)
{
    int i = 0;
    while (arr[i] != -1)
    {
        i++;
    }
    return (i);
}

int main()
{
    int choice,num;
    int flag = 1;
    int min=50,max=200;
    int sayac=0;
    float median,mod;
    int arr[] ={ 
         45,  46,  47,  48,  49,  50,  133,  52,  53,  54,  55,  111,  57,  58,  59,  60, 
         61,  62,  63,  64,  65,  66,  55,  55,  69,  70,  55,  45,  73,  55,  75,  76,
         77,  78,  79,  80,  81,  82,  55,  55,  85,  86,  87,  88,  89,  90,  91,  92,
         93,  193, 95,   133,  76,  191,  55, 100, 101, 102, 76, 104, 105, 106, 107, 108,
        120, 110, 111, 112, 113, 114, 115, 116, 117, 118, 163, 120, 121, 122, 193, 124,
        125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
        141, 193, 133, 144, 145, 146, 147, 148, 149, 150, 151, 193, 153, 154, 155, 156,
        157, 158, 111, 160, 120, 162, 163, 128, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 111, 179, 180, 181, 111, 120, 184, 133, 186, 187, 188,
        125, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 125, 201, 202, 203, 173,
        205,  61, 128, 173,  76, 111, 133, 45, -1};

    int frequencies[250] = {};
    int size = find_size_of_array(arr);
    int number1,number2;
    int i;
    for (i = 0; i <size; i++)
    {
        frequencies[arr[i] - 1]++;
    }
    while ((number1 < 50) || (number2 > 200))
    {
        printf("Enter values A nd B values:\n");
        scanf("%d",&number1);
        scanf("%d",&number2);
    }
    drawHistogram(frequencies,250,arr,number1,number2);
    printf("Would you like to add new numbers(Press 1 for yes,Press 0 for no):");
    scanf("%d",&choice);
     if(choice==1)
    {
        while(flag)
        {
           printf("Enter the numbers(-1 to exit):");
           int count=0;
            while(count<5)
            {
                scanf("%d",&num);
                if(num==-1)
                {
                    flag=0;
                    break;
                }
                add_number(arr,num,&size,number1,number2);
                frequencies[num-1]++;
                count++;
            }
            drawHistogram(frequencies,250,arr,number1,number2);
            float average=calculateAverage(arr,size,number1,number2);
            printf("Average:%.2lf\n",average);
            median=calculateMedian(arr,size,number1,number2);
            printf("Median :%.2lf\n",median);
            mod=calculateMode(arr,size,number1,number2); 
            printf("Mode:%.2lf\n",mod); 
            if(count==5)
            {
                break;
            }  
        }
    }
    if(choice==0)
    {
        float average=calculateAverage(arr,size,number1,number2);
        printf("Average:%.2lf\n",average);
        median=calculateMedian(arr,size,number1,number2);
        printf("Median :%.2lf\n",median);
        mod=calculateMode(arr,size,number1,number2);
        printf("Mode:%.2lf\n",mod);
    }
    else
    {

    }
    return 0;
}