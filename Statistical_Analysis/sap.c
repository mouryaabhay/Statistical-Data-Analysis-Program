// A Statistical Data Analysis Program

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "F:\Untracked Git Files\Statistical_Analysis_C_Program\HeaderFiles\statisticalanalysis.h"

// Read the data from a file and calculate statistical measures
int main(int argc, char *argv[]) {
    // Check number of argument
    if (argc != 2) {
        printf("Error: Please provide exactly one file name as argument.\n");
        return 1;
    }

    // File opening (Where data(Observations) is stored)
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("File opening error");
        fprintf(stderr, "Failed to open the file %s.\n", argv[1]);
        return 1;
    }

    // File opening (Where the result will be stored)
    FILE *dataResult = fopen("DataAnalysisResult.txt", "w+");
    if (dataResult == NULL) {
        perror("File opening error: ");
        fprintf(stderr, "Failed to open the file DataAnalysisResult.txt for writing.\n");
        fclose(fp);
        return 1;
    }

    // Variable declaration realted to observations
    int i, dataCount = 0;
    double Observations, *dataPtr;

    // Count number of observations
    while (fscanf(fp, "%lf", &Observations) == 1) {
        dataCount++;
    }
    
    rewind(fp); // Rewind the file pointer for re-reading

    // Allocate memory after knowing the exact dataCount
    dataPtr = calloc(dataCount, sizeof(double));
    if (dataPtr == NULL) {
        fprintf(stderr, "Memory allocation error! Failed to allocate memory for dataPtr.\n");
        fclose(fp);
        fclose(dataResult);
        return 1;
    }

    // Read data and store it in the allocated array
    for (i = 0; i < dataCount; i++) {
        if (fscanf(fp, "%lf", &Observations) != 1) {
            break; // Exit the loop on error
        }
        dataPtr[i] = Observations; // Read data gets stored in the pointer array
    }

    // Error message (Sent if some data can't be read)
    if (i < dataCount) {
        fprintf(stderr, "Error: Failed to read %d values from the file %s.\n", dataCount - i, argv[1]);
        free(dataPtr);
        fclose(fp);
        fclose(dataResult);
        return 1;
    }


    // Variable declaration related to results

    // Measure of Central Tendency Variables
    double mean = 0.0, median = 0.0;
    double *storeModes = NULL;
    int numberOfModes = 0;

    // Partition Values Variables
    double quartile1 = 0.0, quartile2 = 0.0, quartile3 = 0.0;
    
    // Absolute Measure of Dispersion Variables
    double quartileDeviation = 0.0, range = 0.0, variance = 0.0, standardDeviation = 0.0;
    
    // Relative Measure of Dispersion Variables
    double coefficientOfQuartileDeviation = 0.0, coefficientOfRange = 0.0, coefficientOfVariation = 0.0;

    // Raw Moments Variables
    double dataTotal = 0.0, mu11 = 0.0, mu12 = 0.0, mu13 = 0.0, mu14 = 0.0;

    // Central Moments Variables
    double mu1 = 0.0, mu2 = 0.0, mu3 = 0.0, mu4 = 0.0;

    // Measure of Skewness and Kurtosis Variables
    double Skp = 0.0, Skb = 0.0;

    // Coefficient of Skewness based upon moments
    double beta1 = 0.0, gamma1 = 0.0;

    // Coefficient of Kurtosis
    double beta2 = 0.0, gamma2 = 0.0;


    // Function Calls & Calculations

    // Measure of Central Tendency Function Calls
    mean = MeanFunc(dataPtr, dataCount);
    median = MedianFunc(dataPtr, dataCount);
    ModeFunc(dataPtr, dataCount, &storeModes, &numberOfModes);

    // Partition Values Function Calls
    quartile1 = Quartile1Func(dataPtr, dataCount);
    quartile2 = median; // Because median is quartile 2
    quartile3 = Quartile3Func(dataPtr, dataCount);

    // Absolute Measure of Dispersion Function Calls & Calculations
    quartileDeviation = (quartile3 - quartile1) / 2; // Quartile Deviation Calculation
    range = RangeFunc(dataPtr, dataCount);
    variance = VarianceFunc(dataPtr, dataCount);
    standardDeviation = sqrt(variance);

    // Relative Measure of Dispersion Function Calls & Calculations
    coefficientOfQuartileDeviation = (quartile3 - quartile1) / (quartile3 + quartile1);
    coefficientOfRange = CoefficientOfRangeFunc(dataPtr, dataCount);
    coefficientOfVariation = (standardDeviation / mean) * 100;

    // Raw Moments Function Calls
    mu11 = mean; // Because it is equal to mean (Σxi/n)
    mu12 = Rawmu12(dataPtr, dataCount);
    mu13 = Rawmu13(dataPtr, dataCount);
    mu14 = Rawmu14(dataPtr, dataCount);

    // Central Moments Calculations
    mu2 = mu12 - pow(mu11, 2);
    mu3 = mu13 - (3 * mu12 * mu11) + (2 * pow(mu11, 3));
    mu4 = mu14 - (4 * mu13 * mu11) + (6 * mu12 * pow(mu11, 2)) - (3 * pow(mu11, 4));

    // Measure of Skewness and Kurtosis Calculations
    Skp = 3 * (mean - median) / standardDeviation;
    Skb = ((quartile3 + quartile1) - (2 * quartile2)) / (quartile3 - quartile1);

    // Coefficient of Skewness based upon moments Calculations
    beta1 = pow(mu3, 2) / pow(mu2, 3);
    gamma1 = sqrt(beta1);

    // Coefficient of Kurtosis Calculations
    beta2 = mu4 / pow(mu2, 2);
    gamma2 = beta2 - 3;
    
    
    // Write statistical analysis result in a file

    // Statistical Analysis Result
    fprintf(dataResult, "Statistical Analysis Result\n");
    fprintf(dataResult, "\tNumber of observations(n): %d\n", dataCount);

    // Measure of Central Tendency
    fprintf(dataResult, "  Measure of Central Tendency\n");
    fprintf(dataResult, "\tMean: %.4lf\n", mean);
    fprintf(dataResult, "\tMedian: %.4lf\n", median);
    // Write all the single/multiple modes in the file in formated order 
    fprintf(dataResult, "\tMode(s):\n");
    for (i = 0; i < numberOfModes; i++) {
        int unique, j;
        unique = 1;
        for (j = 0; j < i; j++) {
            if (storeModes[i] == storeModes[j]) {
                unique = 0;
                break;
            }
        }
        if (unique) {
            fprintf(dataResult, "\t  %.4lf\n", storeModes[i]);
        }
    }

    // Partition Values
    fprintf(dataResult, "  Partition Values\n");
    fprintf(dataResult, "\tQuartile 1: %.4lf\n", quartile1);
    fprintf(dataResult, "\tQuartile 2: %.4lf\n", quartile2);
    fprintf(dataResult, "\tQuartile 3: %.4lf\n", quartile3);

    // Absolute Measure of Dispersion
    fprintf(dataResult, "  Absolute Measure of Dispersion\n");
    fprintf(dataResult, "\tQuartile Deviation: %.4lf\n", quartileDeviation);
    fprintf(dataResult, "\tRange: %.4lf\n", range);
    fprintf(dataResult, "\tVariance(σₓ²): %.4lf\n", variance);
    fprintf(dataResult, "\tStandard Deviation(σₓ): %.4lf\n", standardDeviation);

    // Relative Measure of Dispersion
    fprintf(dataResult, "  Relative Measure of Dispersion\n");
    fprintf(dataResult, "\tCoefficient of Quartile Deviation: %.4lf\n", coefficientOfQuartileDeviation);
    fprintf(dataResult, "\tCoefficient of Range: %.4lf\n", coefficientOfRange);
    fprintf(dataResult, "\tCoefficient of Variation: %.4f\n", coefficientOfVariation);

    // Raw Moments
    fprintf(dataResult, "  Raw Moments\n");
    fprintf(dataResult, "\tμ₁': %.4lf\n", mu11);
    fprintf(dataResult, "\tμ₂': %.4lf\n", mu12);
    fprintf(dataResult, "\tμ₃': %.4lf\n", mu13);
    fprintf(dataResult, "\tμ₄': %.4lf\n", mu14);
    
    // Central Moments
    fprintf(dataResult, "  Central Moments\n");
    fprintf(dataResult, "\tμ₁: %.4lf unit\n", mu1);
    fprintf(dataResult, "\tμ₂: %.4lf unit\n", mu2);
    fprintf(dataResult, "\tμ₃: %.4lf unit\n", mu3);
    fprintf(dataResult, "\tμ₄: %.4lf unit\n", mu4);

    // Measure of Skewness and Kurtosis
    fprintf(dataResult, "  Measure of Skewness and Kurtosis\n");

    fprintf(dataResult, "\tSkewness\n"); // Skewness

    // Karl Pearson Coefficient of Skewness
    fprintf(dataResult, "\t\tKarl Pearson Coefficient of Skewness: %.4lf\n", Skp);
    if (Skp > 0) {
        fprintf(dataResult, "\t\t\tHere, Skp > 0.\n\t\t\tTherefore, The given frequency distribution is positively skewed.\n");
    } else if (Skp < 0) {
        fprintf(dataResult, "\t\t\tHere, Skp < 0.\n\t\t\tTherefore, The given frequency distribution is negatively skewed.\n");
    } else {
        fprintf(dataResult, "\t\t\tHere, Skp = 0.\n\t\t\tTherefore, The given frequency distribution is symmetrical (skewness = 0).\n");
    }

    // Bowley's Coefficient of Skewness
    fprintf(dataResult, "\t\tBowley's Coefficient of Skewness: %.4lf\n", Skb);
    if (Skb > 0) {
        fprintf(dataResult, "\t\t\tHere, Skb > 0.\n\t\t\tTherefore, The given frequency distribution is positively skewed.\n");
    } else if (Skb < 0) {
        fprintf(dataResult, "\t\t\tHere, Skb < 0.\n\t\t\tTherefore, The given frequency distribution is negatively skewed.\n");
    } else {
        fprintf(dataResult, "\t\t\tHere, Skb = 0.\n\t\t\tTherefore, The given frequency distribution is symmetrical (skewness = 0).\n");
    }

    // Coefficient of Skewness based upon moments
    fprintf(dataResult, "\tCoefficient of Skewness based upon moments\n");
    fprintf(dataResult, "\t\tβ₁: %.4lf\n", beta1);
    fprintf(dataResult, "\t\t𝛄₁: %.4lf\n", gamma1);
    if (gamma1 > 0) {
        fprintf(dataResult, "\t\t\tHere, 𝛄₁ > 0.\n\t\t\tTherefore, The distribution is positively skewed.\n");
    } else if (gamma1 < 0) {
        fprintf(dataResult, "\t\t\tHere, 𝛄₁ < 0.\n\t\t\tTherefore, The distribution is negatively skewed.\n");
    } else {
        fprintf(dataResult, "\t\t\tHere, 𝛄₁ = 0.\n\t\t\tTherefore, The distribution is symmetrical (skewness = 0).\n");
    }

    // Coefficient of Kurtosis
    fprintf(dataResult, "\tCoefficient of Kurtosis\n");
    fprintf(dataResult, "\t\tβ₂: %.4lf\n", beta2);
    fprintf(dataResult, "\t\t𝛄₂: %.4lf\n", gamma2);
    if (gamma2 > 0) {
        fprintf(dataResult, "\t\t\tHere, 𝛄₁ > 0.\n\t\t\tTherefore, The distribution is Leptokurtic.\n");
    } else if (gamma2 < 0) {
        fprintf(dataResult, "\t\t\tHere, 𝛄₁ < 0.\n\t\t\tTherefore, The distribution is Platykurtic.\n");
    } else {
        fprintf(dataResult, "\t\t\tHere, 𝛄₁ = 0.\n\t\t\tTherefore, The distribution is Mesokurtic.\n");
    }


    // Free the allocated memory
    free(dataPtr);
    free(storeModes);

    // Close files
    fclose(fp);
    fclose(dataResult);

    return 0;
}