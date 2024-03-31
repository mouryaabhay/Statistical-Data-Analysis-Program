#ifndef StatisticalAnalysis_h
#define StatisticalAnalysis_h

// Function to swap two elements (for sorting, used in bubbblesort function)
void swap(double *a, double *b) {
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort the data
void bubbleSort(double *dataPtr, int dataCount) {
    int i, j;
    for (i = 0; i < dataCount - 1; i++) {
        for (j = 0; j < dataCount - i - 1; j++) {
            if (dataPtr[j] > dataPtr[j + 1]) {
                swap(&dataPtr[j], &dataPtr[j + 1]);
            }
        }
    }
}


// Measure of Central Tendency Functions

// Function to find the Mean
double MeanFunc(double *dataPtr, int dataCount) {
    int i;
    double Mean = 0.0;
    for (i = 0; i < dataCount; i++) {
        Mean += dataPtr[i];
    }
    Mean /= (double)dataCount; // Typecast dataCount to double for accurate division
    
    return Mean;
}

// Function to find the Median
double MedianFunc(double *dataPtr, int dataCount) {
    int i, sepDigit = 0;
    double position = 0.0, sepDecimal = 0.0, Median = 0.0;

    bubbleSort(dataPtr, dataCount); // Sort the data to find median

    position = dataCount / 2.0; // This line gives poition value
    sepDigit = (int)position; // Only the whole/integral part is assigned to sepDigit
    sepDecimal = position - sepDigit; // Position(may or may not be in decimal) gets subtracted by integer/digit sepDigit to get value of decimal part

    // NOTE: The data is stored from the location 0, 1, 2, and so on.
    //       So, If the Data set is 1, 2, 3, 4, 5, 6, 7, 8 and the position is 4 (as per position = dataCount / 2) then,
    //                 [Position:   0, 1, 2, 3, 4, 5, 6, 7]
    //       Subtract the position with 1. Because we need to access the 4th data value which is stored at position 3.

    if (dataCount % 2 == 0) {
        if (sepDecimal == 0.0) {
            Median = (dataPtr[sepDigit - 1] + dataPtr[sepDigit]) / 2.0;
        } else {
            Median = dataPtr[sepDigit - 1] + sepDecimal * (dataPtr[sepDigit] - dataPtr[sepDigit - 1]);
        }
    } else {
        Median = dataPtr[sepDigit];
    }
    
    return Median;
}

// Function to find the Mode
void ModeFunc(double dataPtr[], int dataCount, double **storeModes, int *numberOfModes) {

    // Allocate initial memory for a small number of modes
    *storeModes = calloc(4, sizeof(double)); // Start with capacity for 4 modes
    if (*storeModes == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        return;
    }
    *numberOfModes = 0;

    int i, j, count, maxCount = 0;

    for (i = 0; i < dataCount; i++) {
        count = 1;
        for (j = i + 1; j < dataCount; j++) {
            if (dataPtr[i] == dataPtr[j]) {
                count++;
            }
        }

        if (count > maxCount) {
            maxCount = count;
            *numberOfModes = 1;
            (*storeModes)[0] = dataPtr[i];
        } else if (count == maxCount) {
            // If array is full, reallocate more memory
            if (*numberOfModes == 4) {
                *storeModes = realloc(*storeModes, (*numberOfModes + 4) * sizeof(double));
                if (*storeModes == NULL) {
                    fprintf(stderr, "Memory allocation error!\n");
                    return;
                }
            }
            (*storeModes)[*numberOfModes] = dataPtr[i];
            (*numberOfModes)++;
        }
    }
}


// Partition Values Functions

// Function to find the first quartile (Q1)
double Quartile1Func(double *dataPtr, int dataCount) {
    int i, sepDigit = 0;
    double position = 0.0, sepDecimal = 0.0, Quartile1 = 0.0;

    bubbleSort(dataPtr, dataCount);

    position = (dataCount + 1.0) / 4.0; // This line gives poition value
    sepDigit = (int)position; // sepDigit only gets value of whole or integral part assigned
    sepDecimal = position - sepDigit; // Position(may or may not be in decimal) gets subtracted by integer/digit sepDigit to get value of decimal part

    // NOTE: The data is stored from the location 0, 1, 2, and so on.
    //       So, If the Data set is 1, 2, 3, 4, 5, 6, 7, 8 and the position is 4 (as per position = dataCount / 2) then,
    //                 [Position:   0, 1, 2, 3, 4, 5, 6, 7]
    //       Subtract the position with 1. Because we need to access the 4th data value which is stored at position 3.
    
    if (dataCount % 2 == 0) {
        if (sepDecimal == 0.0) {
            Quartile1 = (dataPtr[sepDigit - 1] + dataPtr[sepDigit]) / 2.0;
        } else {
            Quartile1 = dataPtr[sepDigit - 1] + sepDecimal * (dataPtr[sepDigit] - dataPtr[sepDigit - 1]);
        }
    } else {
        Quartile1 = dataPtr[sepDigit];
    }

    return Quartile1;
}

// Function to find the third quartile (Q3)
double Quartile3Func(double *dataPtr, int dataCount) {
    int i, sepDigit = 0;
    double position = 0.0, sepDecimal = 0.0, Quartile3 = 0.0;

    bubbleSort(dataPtr, dataCount);

    position = (3.0 * (dataCount + 1.0)) / 4.0; // This line gives poition value
    sepDigit = (int)position; // sepDigit only gets value of whole or integral part assigned
    sepDecimal = position - sepDigit; // Position(may or may not be in decimal) gets subtracted by integer/digit sepDigit to get value of decimal part

    // NOTE: The data is stored from the location 0, 1, 2, and so on.
    //       So, If the Data set is 1, 2, 3, 4, 5, 6, 7, 8 and the position is 4 (as per position = dataCount / 2) then,
    //                 [Position:   0, 1, 2, 3, 4, 5, 6, 7]
    //       Subtract the position with 1. Because we need to access the 4th data value which is stored at position 3.
    
    if (dataCount % 2 == 0) {
        if (sepDecimal == 0.0) {
            Quartile3 = (dataPtr[sepDigit - 1] + dataPtr[sepDigit]) / 2.0;
        } else {
            Quartile3 = dataPtr[sepDigit - 1] + sepDecimal * (dataPtr[sepDigit] - dataPtr[sepDigit - 1]);
        }
    } else {
        Quartile3 = dataPtr[sepDigit];
    }

    return Quartile3;
}


// Absolute Measure of Dispersion Calculations

// Function to find the Range
double RangeFunc(double *dataPtr, int dataCount) {
    int i;
    double min, max;

    min = max = dataPtr[0]; // Initialize min and max with the first element

    // Loop through the data and update min and max if necessary
    for (i = 1; i < dataCount; i++) {
        if (dataPtr[i] < min) {
            min = dataPtr[i];
        }
        if (dataPtr[i] > max) {
        max = dataPtr[i];
        }
    }

    return max - min; // Return the range (difference between min and max)
}

// Function to find the Variance
double VarianceFunc(double *dataPtr, int dataCount) {
    int i;
    double Variance = 0.0, sumOfObservationsSqr = 0.0;

    // Calculate the sum of squared observations
    for (i = 0; i < dataCount; i++) {
        sumOfObservationsSqr += pow(dataPtr[i], 2);
    }

    Variance = sumOfObservationsSqr / dataCount - pow(MeanFunc(dataPtr, dataCount), 2); // Calculate the variance

    return Variance;
}


// Relative Measure of Dispersion Calculations

// Function to find the coefficient of Range
double CoefficientOfRangeFunc(double *dataPtr, int dataCount) {
    int i;
    double min, max;

    min = max = dataPtr[0]; // Initialize min and max with the first element

    // Loop through the data and update min and max if necessary
    for (i = 1; i < dataCount; i++) {
        if (dataPtr[i] < min) {
            min = dataPtr[i];
        }
        if (dataPtr[i] > max) {
            max = dataPtr[i];
        }
    }

    return (max - min) / (max + min); // Return the range (difference between min and max)
}


// Raw Moments Calculations

// Function to find μ₂'
double Rawmu12(double *dataPtr, int dataCount) {
    int i;
    double mu12 = 0.0, sumOfObservations2 = 0.0;

    // Calculate the sum of squared observations
    for (i = 0; i < dataCount; i++) {
        sumOfObservations2 += pow(dataPtr[i], 2);
    }

    mu12 = sumOfObservations2 / dataCount;

    return mu12;
}

// Function to find μ₃'
double Rawmu13(double *dataPtr, int dataCount) {
    int i;
    double mu13 = 0.0, sumOfObservations3 = 0.0;

    // Calculate the sum of cubed observations
    for (i = 0; i < dataCount; i++) {
        sumOfObservations3 += pow(dataPtr[i], 3);
    }

    mu13 = sumOfObservations3 / dataCount;

    return mu13;
}

// Function to find μ₄'
double Rawmu14(double *dataPtr, int dataCount) {
    int i;
    double mu14 = 0.0, sumOfObservations4 = 0.0;

    // Calculate the sum of tesserected observations
    for (i = 0; i < dataCount; i++) {
        sumOfObservations4 += pow(dataPtr[i], 4);
    }

    mu14 = sumOfObservations4 / dataCount;

    return mu14;
}

#endif