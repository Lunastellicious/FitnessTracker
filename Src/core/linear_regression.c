#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linear_regression.h"

#define MAX_LINE_LENGTH 1024
#define MAX_DATA_POINTS 500
#define MAX_COLUMNS 20

//scv parsing
int parse_csv_line(char* line, double* columns, int max_cols){
    char* token;
    int col = 0;
    line[strcspn(line, "\r\n")] = 0; // removes trailing newline

    token = strtok(line, ","); // tokenizes string
    while( token != NULL && col < max_cols){
        columns[col] = atof(token); // number parsed as (double) and saved in column
        col++;
        token = strtok(NULL, ","); // moves to next token
    }
    return col;
}

//read csv file
int read_csv(const char* filename, dataLoad* a, int* count, int x_col_index, int y_col_index){
    FILE* file = fopen(filename, "r");
    if(!file){
        printf("File failed to read");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    double columns[MAX_COLUMNS];
    *count = 0;

    //Read header line
    if(fgets(line, MAX_LINE_LENGTH, file) != NULL){
        printf("Header: %s", line);
    } else {
        fclose(file);
        return 0;
    }

    while (fgets(line, MAX_LINE_LENGTH, file) && *count < MAX_DATA_POINTS){
        int num_cols = parse_csv_line(line, columns, MAX_COLUMNS);

        if(num_cols > x_col_index && num_cols > y_col_index){
            a[*count].x = columns[x_col_index];
            a[*count].y = columns[y_col_index];
            (*count)++;
        }
    }

    fclose(file);
    return 1;
}

//Calculate LinearRegression
regressionResult calculate_regression(dataLoad* a, int count){
    regressionResult result;
    if(count > MAX_DATA_POINTS*0.2) count -= count*0.2;
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    // Calculate sums
    for (int i = 0; i < count; i++) {
        sum_x += a[i].x;
        sum_y += a[i].y;
        sum_xy += a[i].x * a[i].y;
        sum_x2 += a[i].x * a[i].x;
    }

    //Calculate slope
    double n = (double)count;
    result.slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    result.intercept = (sum_y - result.slope * sum_x) / n;

    // Calculate R-squared
    double ss_tot = 0, ss_err = 0;
    double mean_y = sum_y / n;
    
    for (int i = 0; i < count; i++) {
        double y_pred = result.slope * a[i].x + result.intercept;
        ss_err += (a[i].y - y_pred) * (a[i].y - y_pred);
        ss_tot += (a[i].y - mean_y) * (a[i].y - mean_y);
    }
    
    result.r_squared = 1 - (ss_err / ss_tot);
    printf("ss_res: %lf,\nss_tot: %lf\n", ss_err, ss_tot);
    return result;
}

//function to predict y given x
double predict(dataLoad* x, regressionResult* result){
    return result->slope * x->x + result->intercept;
}

//call
int regression(){
    dataLoad data[MAX_DATA_POINTS];
    int count;
    int x_col_index, y_col_index;

    printf("CSV Linear Regression Tool\n");
    printf("===========================\n\n");

    // Get column indices from user (0-indexed)
    printf("Y is set to column 19 for VO2max\nEnter the column index for X variable (3-16) [4 = km/h]: ");
    scanf("%d", &x_col_index);
    y_col_index = 18;
    
    /* variable y column
    printf("Enter the column index for Y variable (1-8): ");
    scanf("%d", &y_col_index);
    */

    // Validate column indices
    if (x_col_index < 0 || x_col_index > MAX_COLUMNS || 
        y_col_index < 0 || y_col_index > MAX_COLUMNS) {
        printf("Error: Column indices must be between 3 and %d\n", MAX_COLUMNS - 1);
        return 1;
    }
    printf("\n");

    // Read CSV file
    printf("Reading CSV file 'Garmin-runs-50_with_VO2max.csv'...\n");
    if (!read_csv("../../Garmin-runs-50_with_VO2max.csv", data, &count, x_col_index, y_col_index)) {
        return 1;
    }

    printf("Successfully read %d data points\n", count);
    printf("Using column %d as X and column %d as Y\n\n", x_col_index, y_col_index);

    // Display first few data points
    printf("First 5 data points:\n");
    printf("%-15s %-15s\n", "X", "Y");
    printf("------------------------------\n");
    for (int i = 0; i < (count < 5 ? count : 5); i++) {
        printf("%-15.4f %-15.4f\n", data[i].x, data[i].y);
    }
    printf("\n");

    // Calculate linear regression
    regressionResult result = calculate_regression(data, count);

    // Display results
    printf("Linear Regression Results:\n");
    printf("==========================\n");
    printf("Slope:      %.6f\n", result.slope);
    printf("Intercept:  %.6f\n", result.intercept);
    printf("R-squared:  %.6f\n\n", result.r_squared);
    printf("Equation: y = %.6fx + %.6f\n\n", result.slope, result.intercept);

    // Example prediction
    // Should not be printed out til console, but 'test' should just test if the regression is good
    // enough and then if not give an error code or something
    int access;
    double *predicted_y = malloc(100*(sizeof(double)));
    printf("Ready to test? Type 1:\n");
    scanf("%d", &access);
    if (access == 1){
        for(int i = 400; i < 500; i++){
            predicted_y[i-400] = predict(&data[i], &result);
        }
        // Display first few data points
        printf("First 5 data points:\n");
        printf("%-15s %-15s\n", "Y_actual", "Y_predicted");
        printf("------------------------------\n");
        for (int i = 400; i < (count < 405 ? count : 405); i++) {
        printf("%-15.4f %-15.4f\n", data[i].y, predicted_y[i-400]);
        }
        printf("\n");

    }
    free(predicted_y);
    return 0;
}