#include <stdio.h> 
#define MAXPARNUM 17
#define MAXNOTICENUM 12

/* 
    [0]~[3]:   Last 4Q the Day Price 
    [4]~[7]:   Last 4Q after the Day Price  
    [8]~[11]:  Last 4Q Forward EPS 
    [12]~[15]: Last 4Q True EPS 
    [16]:      Next Q Forward EPS
*/

/*輸入參數*/
float INPUT[MAXPARNUM]= 
{0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0};

float META[MAXPARNUM] = 
{298.57, 299.53, 394.78, 493.5, 311.71, 288.35, 474.99, 441.38, 2.91, 3.64, 4.96, 4.32, 2.98, 4.39, 5.33, 4.71, 4.7};
float CSCO[MAXPARNUM] = 
{52.96, 53.28, 50.28, 49.67, 54.73, 48.04, 49.06, 48.34, 1.06, 1.03, 0.84, 0.83, 1.14, 1.11, 0.87, 0.88, 0.8537};
float NVDA[MAXPARNUM] = 
{471.16, 499.44, 674.72, 949.5, 471.63, 487.16, 785.38, 1037.99, 2.07, 3.36, 4.61, 5.59, 2.7, 4.02, 5.16, 6.12, 5.96};
float SNPS[MAXPARNUM] = 
{428.21, 552.46, 543.57, 573.13, 424.10, 498.97, 580.9, 586.30, 2.74, 3.04, 3.43, 3.05, 2.88, 3.17, 3.56, 3.0, 3.2};
float PANW[MAXPARNUM] = 
{209.69, 256.18, 366.09, 318.5, 240.81, 242.30, 261.97, 323.77, 1.28, 1.16, 1.3, 1.25, 1.44, 1.38, 1.46, 1.32, 1.41};
float CRWD[MAXPARNUM] = 
{160.13, 149.18, 212.35, 297.56, 157.55, 163.03, 234.44, 329.57, 0.51, 0.56, 0.74, 0.82, 0.57, 0.74, 0.82, 0.95, 0.8948};
float TW2330[MAXPARNUM] = 
{579.0, 546.0, 588.0, 804.0, 560.0, 556.0, 626.0, 750.0, 6.66, 7.37, 8.65, 8.31, 7.01, 8.14, 9.21, 8.7, 8.83};
float TW2454[MAXPARNUM] = 
{658.0, 857.0, 966.0, 981.0, 690.0, 842.0, 930.0, 1005.0, 8.97, 10.65, 16.14, 15.41, 10.07, 11.64, 16.15, 19.85, 13.79};
float TW6669[MAXPARNUM] = 
{1665.0, 1515.0, 2330.0, 2345.0, 1755.0, 1580.0, 2500.0, 2395.0, 15.86, 15.12, 19.72, 24.94, 14.94, 14.96, 20.1, 26.92, 26.28};
float TW3231[MAXPARNUM] = 
{115.0, 93.2, 122.5, 114.0, 111.5, 94.3, 116.5, 111.0, 1.15, 1.55, 1.17, 1.21, 1.16, 1.67, 1.19, 1.24, 1.35};
float TW1503[MAXPARNUM] = 
{138.5, 101.5, 181.5, 292.0, 136.0, 103.5, 199.5, 284.5, 1.21, 1.15, 0.56, 1.74, 1.14, 1.28, 0.56, 1.93, 1.69}; //士電
float TW1795[MAXPARNUM] = 
{269.0, 240.5, 296.0, 282.0, 250.0, 233.0, 289.5, 287.5, 4.84, 4.75, 1.76, 4.43, 4.85, 4.75, 1.15, 3.96, 5.54}; //美時製藥
/***************************************************/ 

/*********************預測股價*******************/ 
// 前4季公佈財報當天的股價
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    // ... 
}Last4QTheDayPrice; 

// 前4季公佈財報隔天的股價
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    // ... 
}Last4QAfterDayPrice; 

// 下一季公佈財報當天的股價
typedef struct { 
    float Q;
    float Qmax;
    // ... 
}NextQTheDayPrice; 

// 下一季公佈財報隔天的股價
typedef struct { 
    float Q;
    float Qmax;
    // ... 
}NextQAfterDayPrice; 

// 股價結構體
typedef struct { 
    Last4QTheDayPrice last4QTheDayPrice;
    Last4QAfterDayPrice last4QAfterDayPrice;
    NextQTheDayPrice nextQtheDayPrice;
    NextQAfterDayPrice nextQafterDayPrice;
    // ... 
}Price; 
 
/***************************************************/ 
 
/************************EPS**********************/ 
// 前4季實際EPS
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    // ... 
}Last4QTureEPS; 

// 前4季預測EPS
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    // ... 
}Last4QForecastEPS; 

// 下一季預測EPS
typedef struct { 
    float Q; 
    // ... 
}NextQForecastEPS;

// EPS結構體
typedef struct { 
    Last4QTureEPS last4QtureEPS;
    Last4QForecastEPS last4QforecastEPS;
    NextQForecastEPS nextQForecastEPS;
    // ... 
}EPS; 
/***********************************************/ 
 
/***********************PE*********************/ 
// 前4季公布財報當天的PE
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    float QAverage; 
    // ... 
}Last4QTheDayPE; 

// 前4季公布財報隔天的PE
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    float QAverage; 
    // ... 
}Last4QAfterDayPE; 

// PE結構體
typedef struct { 
    Last4QTheDayPE last4QtheDayPE;
    Last4QAfterDayPE last4QafterDayPE;
    // ... 
}PE;
/***************************************************/ 

/*************Q1~Q4的其它參數************/ 
// 前4季EPS差值百分比
typedef struct { 
    float Q1; 
    float Q2; 
    float Q3; 
    float Q4; 
    float QAverage; 
    // ... 
}Lase4QPercenDiff; 

typedef struct{
     Lase4QPercenDiff last4QpercenDiff;
}Others;
/***************************************************/ 

 
/***********************初始化**********************/ 

//初始化發佈財報當天和隔天的股價
void initPrice(Price *price){

    // 前4季發佈財報當天的股價
    price->last4QTheDayPrice.Q1 = INPUT[0]; 
    price->last4QTheDayPrice.Q2 = INPUT[1]; 
    price->last4QTheDayPrice.Q3 = INPUT[2]; 
    price->last4QTheDayPrice.Q4 = INPUT[3]; 
    // 前4季發佈財報隔天的股價
    price->last4QAfterDayPrice.Q1 = INPUT[4]; 
    price->last4QAfterDayPrice.Q2 = INPUT[5]; 
    price->last4QAfterDayPrice.Q3 = INPUT[6]; 
    price->last4QAfterDayPrice.Q4 = INPUT[7]; 
    // 下一季發佈財報當天的股價
    price->nextQtheDayPrice.Q = 0; 
    price->nextQtheDayPrice.Qmax = 0; 
    // 下一季發佈財報隔天的股價
    price->nextQafterDayPrice.Q = 0; 
    price->nextQafterDayPrice.Qmax = 0; 
} 

//初始化預期和實際的EPS
void initEPS(EPS *eps){ 
    // 初始化前4季預期的EPS
    eps->last4QforecastEPS.Q1 = INPUT[8]; 
    eps->last4QforecastEPS.Q2 = INPUT[9]; 
    eps->last4QforecastEPS.Q3 = INPUT[10]; 
    eps->last4QforecastEPS.Q4 = INPUT[11];  
    // 初始化前4季實際的EPS
    eps->last4QtureEPS.Q1 = INPUT[12]; 
    eps->last4QtureEPS.Q2 = INPUT[13]; 
    eps->last4QtureEPS.Q3 = INPUT[14]; 
    eps->last4QtureEPS.Q4 = INPUT[15];
    // 初始化下一季預測的EPS
    eps->nextQForecastEPS.Q = INPUT[16]; 
} 

//初始化發佈財報當天和隔天的PE
void initPE(PE *pe){ 
    // 初始化發佈財報當天的PE
    pe->last4QtheDayPE.Q1 = 0; 
    pe->last4QtheDayPE.Q2 = 0; 
    pe->last4QtheDayPE.Q3 = 0; 
    pe->last4QtheDayPE.Q4 = 0; 
    pe->last4QtheDayPE.QAverage = 0; 
    // 初始化發佈財報隔天的PE
    pe->last4QafterDayPE.Q1 = 0; 
    pe->last4QafterDayPE.Q2 = 0; 
    pe->last4QafterDayPE.Q3 = 0; 
    pe->last4QafterDayPE.Q4 = 0; 
    pe->last4QafterDayPE.QAverage = 0; 
} 

//初始化其它參數
void initOthers(Others *others){ 
    // 初始化EPS差值百分比
    others->last4QpercenDiff.Q1 = 0; 
    others->last4QpercenDiff.Q2 = 0; 
    others->last4QpercenDiff.Q3 = 0; 
    others->last4QpercenDiff.Q4 = 0; 
    others->last4QpercenDiff.QAverage = 0; 
} 


/**
 * @brief 將輸入數組的值複製到全局數組中
 * 
 * 这个函数将输入数组中的值复制到名为 INPUT 的全局数组中。
 *
 * @param input 要复制的输入数组
 */
void initInput(float input[MAXPARNUM]){
    int i=0;
    for(i=0; i<MAXPARNUM; i++)
    {
        INPUT[i] = input[i];
    }
}

/*
 * lastFourQuartersTheDayForwardAveragePE 函數用於計算"- 計算前四季發佈財報當天Forward PE的平均值" 
 * @param Price *price 發佈財報當天股價
 * @param EPS *eps 預期EPS
 * @param PE *pe PE *pe 發佈財報當天PE的平均值
 * @return  PE *pe 發佈財報當天PE的平均值
 */ 
float lastFourQuartersTheDayForwardAveragePE(Price *price, EPS *eps, PE *pe){ 

    // 計算前4季發佈財報當天的PE
    pe->last4QtheDayPE.Q1 = price->last4QTheDayPrice.Q1 / eps->last4QtureEPS.Q1;
    pe->last4QtheDayPE.Q2 = price->last4QTheDayPrice.Q2 / eps->last4QtureEPS.Q2;
    pe->last4QtheDayPE.Q3 = price->last4QTheDayPrice.Q3 / eps->last4QtureEPS.Q3;
    pe->last4QtheDayPE.Q4 = price->last4QTheDayPrice.Q4 / eps->last4QtureEPS.Q4;
 
     // 計算前4季發佈財報當天PE的平均值
     pe->last4QtheDayPE.QAverage = 
     (  pe->last4QtheDayPE.Q1 
        +pe->last4QtheDayPE.Q2
        +pe->last4QtheDayPE.Q3
        +pe->last4QtheDayPE.Q4 ) / 4;
 
    return pe->last4QtheDayPE.QAverage; 
} 

/*
 * lastFourQuartersAfterDayForwardAveragePE 函數用於計算"- 計算前四季發佈財報隔天Forward PE的平均值" 
 * @param Price *price 發佈財報隔天股價
 * @param EPS *eps 預期EPS
 * @param PE *pe PE *pe 發佈財報隔天PE的平均值
 * @return  PE *pe 發佈財報隔天PE的平均值
 */ 
float lastFourQuartersAfterDayForwardAveragePE(Price *price, EPS *eps, PE *pe){ 

    // 計算前4季發佈財報當天的PE
    pe->last4QafterDayPE.Q1 = price->last4QAfterDayPrice.Q1 / eps->last4QtureEPS.Q1;
    pe->last4QafterDayPE.Q2 = price->last4QAfterDayPrice.Q2 / eps->last4QtureEPS.Q2;
    pe->last4QafterDayPE.Q3 = price->last4QAfterDayPrice.Q3 / eps->last4QtureEPS.Q3;
    pe->last4QafterDayPE.Q4 = price->last4QAfterDayPrice.Q4 / eps->last4QtureEPS.Q4;
 
     // 計算前4季發佈財報當天PE的平均值
     pe->last4QafterDayPE.QAverage = 
     (  pe->last4QafterDayPE.Q1 
        +pe->last4QafterDayPE.Q2
        +pe->last4QafterDayPE.Q3
        +pe->last4QafterDayPE.Q4 ) / 4;
 
    return pe->last4QafterDayPE.QAverage; 
}

/*
 * lastFourQuartersPercentagDiffAverageEPS 函數用於計算"- 前4季預測與實際的EPS差值百分比平均值" 
 * @param EPS *eps 實際EPS
 * @param Others *others 前4季預測與實際的EPS差值百分比平均值
 * @return Others *others 前4季預測與實際的EPS差值百分比平均值
 */ 
float lastFourQuartersPercentagDiffAverageEPS(EPS *eps, Others *others){ 

    // 計算前4季的EPS差值百分比
    others->last4QpercenDiff.Q1 = ((eps->last4QtureEPS.Q1) - (eps->last4QforecastEPS.Q1)) / eps->last4QforecastEPS.Q1;
    others->last4QpercenDiff.Q2 = (eps->last4QtureEPS.Q2 - eps->last4QforecastEPS.Q2) / eps->last4QforecastEPS.Q2;
    others->last4QpercenDiff.Q3 = (eps->last4QtureEPS.Q3 - eps->last4QforecastEPS.Q3) / eps->last4QforecastEPS.Q3;
    others->last4QpercenDiff.Q4 = (eps->last4QtureEPS.Q4 - eps->last4QforecastEPS.Q4) / eps->last4QforecastEPS.Q4;
 
     // 計算前4季發佈財報當天PE的平均值
     others->last4QpercenDiff.QAverage = 
     (  others->last4QpercenDiff.Q1 
        + others->last4QpercenDiff.Q2
        + others->last4QpercenDiff.Q3
        + others->last4QpercenDiff.Q4 ) / 4;
 
    return others->last4QpercenDiff.QAverage; 
} 
 
 /*
 * nextQuarterTheDayMaxPrice 函數用於計算" 下一季財財報公布當天的股價最大值 " 
 * @param PE *pe 前4季發布財報當天的PE的平均值
 * @param EPS *eps 下一季預測的EPS
 * @param Others *others 前4季預測與實際的EPS差值百分比平均值
 * @param Price *price 
 * @return Price *price 下一季財財報公布當天的股價最大值
 */ 
float nextQuarterTheDayMaxPrice(PE *pe, EPS *eps, Others *others, Price *price){ 

    price->nextQtheDayPrice.Qmax = 
    pe->last4QtheDayPE.QAverage * (eps->nextQForecastEPS.Q * (1 + others->last4QpercenDiff.QAverage));
 
    return price->nextQtheDayPrice.Qmax; 
}

 /*
 * nextQuarterTheDayPrice 函數用於計算" 下一季財財報公布當天的股價 " 
 * @param PE *pe 前4季發布財報當天的PE的平均值
 * @param EPS *eps 下一季預測的EPS
 * @param Price *price 
 * @return Price *price 下一季財財報公布當天的股價
 */ 
float nextQuarterTheDayPrice(PE *pe, EPS *eps, Price *price){ 

    price->nextQtheDayPrice.Q = 
    pe->last4QtheDayPE.QAverage * eps->nextQForecastEPS.Q;
 
    return price->nextQtheDayPrice.Q; 
}

/*
 * nextQuarterAfterDayMaxPrice 函數用於計算" 下一季財報公布隔天的股價最大值 " 
 * @param PE *pe 前4季發布財報隔天的PE的平均值
 * @param EPS *eps 下一季預測的EPS
 * @param Others *others 前4季預測與實際的EPS差值百分比平均值
 * @param Price *price 
 * @return Price *price 下一季財報公布隔天的股價最大值
 */ 
float nextQuarterAfterDayMaxPrice(PE *pe, EPS *eps, Others *others, Price *price){ 

    price->nextQafterDayPrice.Qmax = 
    pe->last4QafterDayPE.QAverage * (eps->nextQForecastEPS.Q * (1 + others->last4QpercenDiff.QAverage));
 
    return price->nextQafterDayPrice.Qmax; 
}

 /*
 * nextQuarterAfterDayPrice 函數用於計算" 下一季財報公布隔天的股價 " 
 * @param PE *pe 前4季發布財報隔天的PE的平均值
 * @param EPS *eps 下一季預測的EPS
 * @param Price *price 
 * @return Price *price 下一季財財報公布隔天的股價
 */ 
float nextQuarterAfterDayPrice(PE *pe, EPS *eps, Price *price){ 

    price->nextQafterDayPrice.Q = 
    pe->last4QafterDayPE.QAverage * eps->nextQForecastEPS.Q;
 
    return price->nextQafterDayPrice.Q; 
}

 /*
 * profitPercentage 函數用於計算" 預期的獲利百分比 " 
 * @param CurrentPrice 現在價格
 * @param ForwardPrice 預期價格
 * @return Price *price 預期的獲利百分比 
 */ 
float profitPercentage(float CurrentPrice ,float ForwardPrice){
    float ProfitPercentage;
    ProfitPercentage = (ForwardPrice - CurrentPrice) / CurrentPrice * 100.0;
    return ProfitPercentage;
}
/*
* 比较函数 compar 是一个用户定义的函数，用于定义数组元素的排序规则。它接受两个参数，这两个参数都是指向待比较元素的指针。该函数返回一个整数值，表示两个元素的大小关系：
*
* 如果返回值小于 0，则表示第一个元素应该排在第二个元素之前。
* 如果返回值等于 0，则表示两个元素相等，顺序不变。
* 如果返回值大于 0，则表示第一个元素应该排在第二个元素之后。
*/
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
 
 
int main() { 
    
    int j = 0;
    int order = 0 ;
    char stockName[20];
    float l4qtdfaPE;
    float l4qadfaPE;
    float l4qpdaEPS;
    float nqtdmaxPrice, nqtdmaxProfitPercentage;
    float nqtdPrice, nqtdProfitPercentage;
    float nqadmaxPrice, nqadmaxPercentage;
    float nqadPrice, nqadProfitPercentage;
    float CurrentPrice;
    int NextQdate;

    Price myPrice; 
    EPS myEPS; 
    PE myPE;
    Others myOthers; 

    float orderPrice[4];
    float orderPercentage[4];
    int numberPrice = sizeof(orderPrice) / sizeof(orderPrice[0]);
    int numberPercentage = sizeof(orderPercentage) / sizeof(orderPercentage[0]);

    FILE *fp;
    char filename[50];

    printf("請輸入文件名(試算日期): ");
    scanf("%s", filename);
    // 打開文件，如果文件不存在則創建
    fp = fopen(filename, "w");
    fp = fopen(filename, "a");
    // 檢查文件是否成功打開
    if(fp == NULL){
        printf("無法打開文件或文件不存在.\n");
        return 1;
    }
    
    printf("stockName \tcurrentPrice \t\tNextQdate \t\tPrice  \t\t\t\tmaxPrice \n");
    fprintf(fp, "stockName \tcurrentPrice \tNextQdate \t\tPrice  \t\t\t\t\tmaxPrice \n");

    for(j=0; j<MAXNOTICENUM; j++)
    {
        if(j == 0){
            strcpy(stockName, "META");
            CurrentPrice = 478.22;
            NextQdate = 20240724;
            initInput(META);
        }
        else if(j == 1){
            strcpy(stockName, "CSCO");
            CurrentPrice = 46.42;
            NextQdate = 20240814;
            initInput(CSCO);
        }
        else if(j == 2){
            strcpy(stockName, "NVDA");
            CurrentPrice = 1064.69;
            NextQdate = 20240815;
            initInput(NVDA);
        }
        else if(j == 3){
            strcpy(stockName, "SNPS");
            CurrentPrice = 587.4;
            NextQdate = 20240821;
            initInput(SNPS);
        }
        else if(j == 4){
            strcpy(stockName, "PANW");
            CurrentPrice = 321.6;
            NextQdate = 20240905;
            initInput(PANW);
        }
        else if(j == 5){
            strcpy(stockName, "CRWD");
            CurrentPrice = 351.47;
            NextQdate = 20240604;
            initInput(CRWD);
        }
        else if(j == 6){
            strcpy(stockName, "台積電");
            CurrentPrice = 867.0;
            NextQdate = 20240718;
            initInput(TW2330);
        }
        else if(j == 7){
            strcpy(stockName, "聯發科");
            CurrentPrice = 1195.0;
            NextQdate = 20240726;
            initInput(TW2454);
        }
        else if(j == 8){
            strcpy(stockName, "緯穎");
            CurrentPrice = 2740.0;
            NextQdate = 20240807;
            initInput(TW6669);
        }
        else if(j == 9){
            strcpy(stockName, "緯創");
            CurrentPrice = 115.0;
            NextQdate = 20240801;
            initInput(TW3231);
        }
        else if(j == 10){
            strcpy(stockName, "士電");
            CurrentPrice = 238.5;
            NextQdate = 20240802;
            initInput(TW3231);
        }
        else if(j == 11){
            strcpy(stockName, "美時製藥");
            CurrentPrice = 280.0;
            NextQdate = 20240808;
            initInput(TW1795);
        }
        else
        {
            printf("Done!\r\n");
            while(1);
        }

        initPrice(&myPrice); 
        initEPS(&myEPS); 
        initPE(&myPE); 
        initOthers(&myOthers);
        
        /** 計算PE, 預估和實際EPS的差值**********************************************/
        l4qtdfaPE = lastFourQuartersTheDayForwardAveragePE(&myPrice, &myEPS, &myPE);
    //     printf("Last 4 Quarters The Day Forward Average PE: %3f\n", l4qtdfaPE); 

        l4qadfaPE = lastFourQuartersAfterDayForwardAveragePE(&myPrice, &myEPS, &myPE);
    //     printf("Last 4 Quarters After Day Forward Average PE: %3f\n", l4qadfaPE);

        l4qpdaEPS = lastFourQuartersPercentagDiffAverageEPS(&myEPS, &myOthers);
    //     printf("Last 4 Quarters Percentag Difference Average EPS: %3f\n", l4qpdaEPS);



        /** 計算季報 當日/隔日 的 合理價/最高價**************************************/
        nqtdmaxPrice = nextQuarterTheDayMaxPrice(&myPE, &myEPS, &myOthers, &myPrice);
    //    nqtdmaxProfitPercentage = profitPercentage(CurrentPrice, nqtdmaxPrice);
    //    printf("Next Quarter The Day Max\t Price: %3f, up %.2f%%\n", nqtdmaxPrice, nqtdmaxProfitPercentage);

        nqtdPrice = nextQuarterTheDayPrice(&myPE, &myEPS, &myPrice); 
    //    nqtdProfitPercentage = profitPercentage(CurrentPrice, nqtdPrice);
    //    printf("Next Quarter The Day\t\t Price: %3f, up %.2f%%\n", nqtdPrice, nqtdProfitPercentage);

        nqadmaxPrice = nextQuarterAfterDayMaxPrice(&myPE, &myEPS, &myOthers, &myPrice); 
    //    nqadmaxPercentage = profitPercentage(CurrentPrice, nqadmaxPrice);
    //    printf("Next Quarter After Day Max\t Price: %3f, up %.2f%%\n", nqadmaxPrice, nqadmaxPercentage);

        nqadPrice = nextQuarterAfterDayPrice(&myPE, &myEPS, &myPrice); 
    //    nqadProfitPercentage = profitPercentage(CurrentPrice, nqadPrice);
    //    printf("Next Quarter After Day\t\t Price: %3f, up %.2f%%\n", nqadPrice, nqadProfitPercentage);
        
        orderPrice[0] = nqtdmaxPrice;
        orderPrice[1] = nqtdPrice;
        orderPrice[2] = nqadmaxPrice;
        orderPrice[3] = nqadPrice;
        qsort(orderPrice, numberPrice, sizeof(float), compare);

        orderPercentage[0] = profitPercentage(CurrentPrice, orderPrice[0]);
        orderPercentage[3] = profitPercentage(CurrentPrice, orderPrice[3]);


        /** 輸出預期價格資訊和文件*********************************************************/
        // printf("%s:  \t\t%.3f \t\t%.3f,up%.2f%% \t%.3f,up%.2f%% \t%.3f,up%.2f%% \t%.3f,up%.2f%%\n", stockName, CurrentPrice,
        // nqtdmaxPrice, nqtdmaxProfitPercentage, nqtdPrice, nqtdProfitPercentage,
        // nqadmaxPrice, nqadmaxPercentage, nqadPrice, nqadProfitPercentage);       

        printf("%s: \t\t%.3f \t\t%d \t\t%.3f %.2f%% \t\t%.3f %.2f%%\n", 
        stockName, CurrentPrice, NextQdate,
        orderPrice[0], orderPercentage[0], orderPrice[numberPrice - 1], orderPercentage[numberPercentage - 1]);   

        fprintf(fp, "%s: \t\t%.3f \t\t%d \t\t%.3f %.2f%% \t\t%.3f %.2f%%\n", 
        stockName, CurrentPrice, NextQdate,
        orderPrice[0], orderPercentage[0], orderPrice[numberPrice - 1], orderPercentage[numberPercentage - 1]); 
    }

    // 關閉文件
    fclose(fp);
    printf("內容已成功寫入 %s.txt\n", filename);
    return 0; 
}