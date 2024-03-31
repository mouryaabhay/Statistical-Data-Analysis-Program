// Linear Correlation and Regression Analysis C Program

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "F:\Git Files\Statistical_Data_Analysis_Program\HeaderFiles\statisticalanalysis.h"

// Read the data from a file and calculate statistical measures
int main(int argc, char *argv[]) {
    // Check number of argument
    if (argc != 3) {
        printf("Error: Please provide exactly two file name as argument which include xi and yi data respectively.\n");
        return 1;
    }

    // File opening (Where data(xiObservations) is stored)
    FILE *xiFP = fopen(argv[1], "r");
    if (xiFP == NULL) {
        perror("File opening error");
        fprintf(stderr, "Failed to open the file %s.\n", argv[1]);
        return 1;
    }
    FILE *yiFP = fopen(argv[2], "r");
    if (yiFP == NULL) {
        perror("File opening error");
        fprintf(stderr, "Failed to open the file %s.\n", argv[2]);
        return 1;
    }

    // File opening (Where the result will be stored)
    FILE *dataResult = fopen("Linear_Correlation_and_Regression_Analysis_Result.txt", "w+");
    if (dataResult == NULL) {
        perror("File opening error: ");
        fprintf(stderr, "Failed to open the file Linear_Correlation_and_Regression_Analysis_Result.txt for writing.\n");
        fclose(xiFP);
        fclose(yiFP);
        return 1;
    }

    // Variable declaration realted to observations
    int i, xiDataCount = 0, yiDataCount = 0;
    double xiObservations, yiObservations, *xiDataPtr, *yiDataPtr;

    // Count number of observations
    while (fscanf(xiFP, "%lf", &xiObservations) == 1) {
        xiDataCount++;
    }
    while (fscanf(yiFP, "%lf", &yiObservations) == 1) {
        yiDataCount++;
    }
    
    // Rewind the file pointer for re-reading
    rewind(xiFP);
    rewind(yiFP);

    // Allocate memory after knowing the exact xiDataCount
    xiDataPtr = calloc(xiDataCount, sizeof(double));
    if (xiDataPtr == NULL) {
        fprintf(stderr, "Memory allocation error! Failed to allocate memory for xiDataPtr.\n");
        fclose(xiFP);
        fclose(dataResult);
        return 1;
    }
    yiDataPtr = calloc(yiDataCount, sizeof(double));
    if (yiDataPtr == NULL) {
        fprintf(stderr, "Memory allocation error! Failed to allocate memory for yiDataPtr.\n");
        fclose(yiFP);
        fclose(dataResult);
        return 1;
    }

    // Read data and store it in the allocated array
    for (i = 0; i < xiDataCount; i++) {
        if (fscanf(xiFP, "%lf", &xiObservations) != 1) {
            break; // Exit the loop on error
        }
        xiDataPtr[i] = xiObservations; // Read data gets stored in the pointer array
    }
    for (i = 0; i < yiDataCount; i++) {
        if (fscanf(yiFP, "%lf", &yiObservations) != 1) {
            break; // Exit the loop on error
        }
        yiDataPtr[i] = yiObservations; // Read data gets stored in the pointer array
    }

    // Error message (Sent if some data can't be read)
    if (i < xiDataCount) {
        fprintf(stderr, "Error: Failed to read %d values from the file %s.\n", xiDataCount - i, argv[1]);
        free(xiDataPtr);
        fclose(xiFP);
        fclose(dataResult);
        return 1;
    }
    if (i < xiDataCount) {
        fprintf(stderr, "Error: Failed to read %d values from the file %s.\n", yiDataCount - i, argv[2]);
        free(yiDataPtr);
        fclose(yiFP);
        fclose(dataResult);
        return 1;
    }


    // Variable declaration
    int numberOfObservations;
    double xiMean = 0.0, yiMean = 0.0;
    double xiVariance = 0.0, yiVariance = 0.0;
    double xiStandardDeviation = 0.0, yiStandardDeviation = 0.0;
    double sumOfxiObservations = 0.0, sumOfyiObservations = 0.0, productOfxiyiObservations = 0.0;
    double covxy = 0.0, covariance = 0.0;
    double byx = 0.0, a1 = 0.0;
    double bxy = 0.0, a2 = 0.0;
    double coefficientOfCorrelation = 0.0;


    // Function Calls & Calculations
    numberOfObservations = xiDataCount;
    xiMean = MeanFunc(xiDataPtr, xiDataCount);
    yiMean = MeanFunc(yiDataPtr, yiDataCount);
    xiVariance = VarianceFunc(xiDataPtr, xiDataCount);
    yiVariance = VarianceFunc(yiDataPtr, yiDataCount);
    xiStandardDeviation = sqrt(xiVariance);
    yiStandardDeviation = sqrt(yiVariance);

    for (i = 0; i < numberOfObservations; i++) {
        sumOfxiObservations += xiDataPtr[i];
    }
    for (i = 0; i < numberOfObservations; i++) {
        sumOfyiObservations += yiDataPtr[i];
    }
    for (i = 0; i < numberOfObservations; i++) {
        productOfxiyiObservations += (xiDataPtr[i] * yiDataPtr[i]);
    }

    covxy = (productOfxiyiObservations / numberOfObservations) - (xiMean * yiMean);
    covariance = covxy / (xiStandardDeviation * yiStandardDeviation);

    // The regression equation of line Y on X Calculations
    byx = covxy / xiVariance;
    a1 = yiMean - (byx * xiMean);

    // The regression equation of line X on Y Calculations
    bxy = covxy / yiVariance;
    a2 = xiMean - (bxy * yiMean);

    coefficientOfCorrelation = covxy / (xiStandardDeviation * yiStandardDeviation);
    
    
    // Write analysis result in a file

    // Linear Correlation and Regression Analysis Result
    fprintf(dataResult, "Linear Correlation and Regression Analysis Result\n");
    fprintf(dataResult, "  Number of xi observations(N): %d\n", numberOfObservations);
    fprintf(dataResult, "\tMean(x̄): %.4lf\n", xiMean);
    fprintf(dataResult, "\tMean(ȳ): %.4lf\n", yiMean);
    fprintf(dataResult, "\tVariance(σₓ²): %.4lf\n", xiVariance);
    fprintf(dataResult, "\tVariance(σᵧ²): %.4lf\n", yiVariance);
    fprintf(dataResult, "\tStandard Deviation(σₓ): %.4lf\n", xiStandardDeviation);
    fprintf(dataResult, "\tStandard Deviation(σᵧ): %.4lf\n", yiStandardDeviation);
    fprintf(dataResult, "\tCovariance (cov(x, y)): %.4lf\n", covariance);

    // The regression equation of line Y on X
    fprintf(dataResult, "  The regression equation of line Y on X\n");
    fprintf(dataResult, "\tbyx: %.4lf\n", byx);
    fprintf(dataResult, "\ta = ȳ - byxx̄: %.4lf\n", a1);
    fprintf(dataResult, "\tY = a + byxX: %.4lf + %.4lf(X)\n", a1, byx);

    // The regression equation of line X on Y
    fprintf(dataResult, "  The regression equation of line X on Y\n");
    fprintf(dataResult, "\tbxy: %.4lf\n", bxy);
    fprintf(dataResult, "\ta = x̄ - bxyȳ: %.4lf\n", a2);
    fprintf(dataResult, "\tX = a + bxyY: %.4lf + %.4lf(Y)\n", a2, bxy);

    fprintf(dataResult, "  Coefficient of correlation(r): %.4lf\n", coefficientOfCorrelation);
    fprintf(dataResult, "  Explanatory Power of the models(r²): %.4lf\n", pow(coefficientOfCorrelation, 2));


    // Free the allocated memory
    free(xiDataPtr);
    free(yiDataPtr);

    // Close files
    fclose(xiFP);
    fclose(yiFP);
    fclose(dataResult);

    return 0;
}