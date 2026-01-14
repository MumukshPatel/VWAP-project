#include <stdio.h>

int main() {
    FILE *fp = fopen("data.csv", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    char line[200];
    char date[20];

    double open, high, low, close;
    long long volume;

    double avgPrice;
    double totalPV = 0.0;
    long long totalVolume = 0;

    int dayCount = 0;

    /* Skip header */
    int days;
    fscanf(fp,"%d",&days);
    fgets(line,sizeof(line),fp);
    fgets(line, sizeof(line), fp);

    /* Read first 15 days */
    while (fgets(line, sizeof(line), fp) && dayCount <=days) {

        sscanf(line, "%[^,],%lf,%lf,%lf,%lf,%lld",
               date, &open, &high, &low, &close, &volume);

        avgPrice = (open + high + low + close) / 4.0;

        totalPV += avgPrice * volume;
        totalVolume += volume;

        printf("Day %d | %s | Avg Price = %.2lf\n",
               dayCount + 1, date, avgPrice);

        dayCount++;
    }

    fclose(fp);

    if (totalVolume > 0) {
        double vwap = totalPV / totalVolume;
        printf("\n VWAP = %.2lf\n",vwap);
    } else {
        printf("VWAP cannot be calculated\n");
    }

    return 0;
}
