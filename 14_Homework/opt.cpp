//好了现在来说明一下我的目的：
//你需要优化已给出的calculate1函数并实现calculate2函数，使其在输出正确结果的情况下拥有尽可能短的
//运行时间。你只能更改calculate函数的内容，增加
//或删除如getdata一样的辅助函数，不允许修改其他内容

/*
最初的运行速度：
NO SIMD cost 0.254453 seconds
SIMD cost 0 seconds     （废话你压根就没写calculate2呢）

原函数如下：
void calculate1(int n)
{
    long long sum_qty = 0, sum_base_price = 0;
    double sum_disc_price = 0, sum_charge = 0, sum_discount = 0, avg_qty = 0, avg_price = 0, avg_disc = 0;
    size_t count_order = 0;
    for (int a = 0; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)
        {
            sum_qty += getdata(&Table, Table.quantity, a);
        }
    }
    for (int a = 0; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)
        {
            sum_base_price += getdata(&Table, Table.price, a);
        }
    }
    for (int a = 0; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)
        {
            sum_discount += getdata(&Table, Table.discount, a);
        }
    }
    for (int a = 0; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)
        {
            sum_disc_price += getdata(&Table, Table.price, a) * (1 - getdata(&Table, Table.discount, a));
        }
    }
    for (int a = 0; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)
        {
            sum_charge += getdata(&Table, Table.price, a) * (1 - getdata(&Table, Table.discount, a)) * (1 + getdata(&Table, Table.tax, a));
        }
    }
    for (int a = 0; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)
        {
            count_order++;
        }
    }
    SumQuantity = sum_qty;
    SumBasePrice = sum_base_price;
    SumDiscPrice = sum_disc_price;
    SumCharge = sum_charge;
    AvgQuantity = SumQuantity / Table.num;
    AvgPrice = SumBasePrice / Table.num;
    AvgDiscount = sum_discount / Table.num;
    total = count_order;
}

void calculate2(int n)
{

}


进行循环合并后：
NO SIMD cost 0.093904 seconds
SIMD cost 0 seconds

进行数据重用后
NO SIMD cost 0.074149 seconds
SIMD cost 0 seconds

calculate2启动线程
*/




#include <iostream>     
#include "opt.h"


#include <immintrin.h> //引入指令集以便编写2
#include <thread>
#include <vector>
//#include <mutex>

//std::mutex mtx;  // 互斥锁，用于保护共享资源


table Table;
double SumQuantity, SumBasePrice, SumDiscPrice, SumCharge, AvgQuantity, AvgPrice, AvgDiscount;
size_t total;

int getdata(table* table, int* ptr, int index)
{
    if (index < 0 || index >= table->num)
        return 0;
    else
        return ptr[index];
}

double getdata(table* table, double* ptr, int index)
{
    if (index < 0 || index >= table->num)
        return 0;
    else
        return ptr[index];
}

// void calculate21(int n)     //把名字进行了一个更改以区分进一步优化后的函数（没有循环展开的）
// {
//     long long sum_qty = 0, sum_base_price = 0;
//     double sum_disc_price = 0, sum_charge = 0, sum_discount = 0, avg_qty = 0;
//     double avg_price = 0, avg_disc = 0;     //原来的换行太阴间了
//     size_t count_order = 0;
//     int table_num = Table.num;      //提取出判断条件
//     int price = 0;
//     double discount = 0;
//     double oneMdiscount = 0;
//     double PandOneDis = 0;
//     //double tax = 0;
//     for (int a = 0; a < table_num; a++) //写这么多分开的循环可太棒了
//     {
//         int date = getdata(&Table, Table.date, a);
//         if (date <= n)          //进行一个计算结果的复用
//         {
//             price  = getdata(&Table, Table.price, a);
//             discount = getdata(&Table, Table.discount, a);
//             oneMdiscount = 1 - discount;
//             PandOneDis = price * oneMdiscount;
//             //tax = 

//             sum_qty += getdata(&Table, Table.quantity, a);
//             sum_base_price += price;
//             sum_discount += discount;
//             sum_disc_price += PandOneDis;
//             sum_charge += PandOneDis * (1 + getdata(&Table, Table.tax, a));
//             count_order++;
//         }
//     }
//     SumQuantity = sum_qty;
//     SumBasePrice = sum_base_price;
//     SumDiscPrice = sum_disc_price;
//     SumCharge = sum_charge;
//     AvgQuantity = SumQuantity / table_num;
//     AvgPrice = SumBasePrice / table_num;
//     AvgDiscount = sum_discount / table_num;
//     total = count_order;
// }

void calculate1(int n)      //经过循环展开的
{
    long long sum_qty = 0, sum_base_price = 0;
    double sum_disc_price = 0, sum_charge = 0, sum_discount = 0, avg_qty = 0;
    double avg_price = 0, avg_disc = 0;     

    size_t count_order = 0;
    int table_num = Table.num;      
    int price = 0;
    double discount = 0;
    double oneMdiscount = 0;
    double PandOneDis = 0;

    int price1 = 0;
    double discount1 = 0;
    double oneMdiscount1 = 0;
    double PandOneDis1 = 0;

    int price2 = 0;
    double discount2 = 0;
    double oneMdiscount2 = 0;
    double PandOneDis2 = 0;
    //double tax = 0;

    // 2*2循环展开的思想是每次迭代处理两个元素，从而减少循环次数和循环控制的开销
    // 为了保证正确性，需要考虑table_num是否为偶数，以及循环边界的处理
    // 另外，为了避免重复计算，可以将一些常量和中间变量提取出来
    int half_table_num = table_num / 2; // 计算table_num的一半，向下取整
    //double one_plus_tax = 1 + getdata(&Table, Table.tax, 0); // 假设税率是固定的，只需获取一次
    int a = 0; // 循环变量
    // 处理前半部分的元素，每次两个
    for (; a < half_table_num * 2; a += 2) 
    {
        int date1 = getdata(&Table, Table.date, a); // 获取第一个元素的日期
        int date2 = getdata(&Table, Table.date, a + 1); // 获取第二个元素的日期
        if (date1 <= n && date2 <= n) // 如果两个元素都满足条件
        {
            // 获取两个元素的价格和折扣，并计算相关的值
            price1  = getdata(&Table, Table.price, a);
            price2  = getdata(&Table, Table.price, a + 1);

            discount1 = getdata(&Table, Table.discount, a);
            discount2 = getdata(&Table, Table.discount, a + 1);

            oneMdiscount1 = 1 - discount1;
            oneMdiscount2 = 1 - discount2;

            PandOneDis1 = price1 * oneMdiscount1;
            PandOneDis2 = price2 * oneMdiscount2;


            // 累加相关的值
            sum_qty += getdata(&Table, Table.quantity, a) + getdata(&Table, Table.quantity, a + 1);
            sum_base_price += price1 + price2;
            sum_discount += discount1 + discount2;
            sum_disc_price += PandOneDis1 + PandOneDis2;
            sum_charge += PandOneDis1 * (1 + getdata(&Table, Table.tax, a)) 
                        + PandOneDis2 * (1 + getdata(&Table, Table.tax, a+1));
            count_order += 2; // 增加两个订单的数量
        }
        else if (date1 <= n) // 如果只有第一个元素满足条件
        {
            // 获取第一个元素的价格和折扣，并计算相关的值
            int price1  = getdata(&Table, Table.price, a);
            double discount1 = getdata(&Table, Table.discount, a);
            double oneMdiscount1 = 1 - discount1;
            double PandOneDis1 = price1 * oneMdiscount1;

            // 累加相关的值
            sum_qty += getdata(&Table, Table.quantity, a);
            sum_base_price += price1;
            sum_discount += discount1;
            sum_disc_price += PandOneDis1;
            sum_charge += PandOneDis1 * (1 + getdata(&Table, Table.tax, a));
            count_order++; // 增加一个订单的数量
        }
        else if (date2 <= n) // 如果只有第二个元素满足条件
        {
            // 获取第二个元素的价格和折扣，并计算相关的值
            int price2  = getdata(&Table, Table.price, a + 1);
            double discount2 = getdata(&Table, Table.discount, a + 1);
            double oneMdiscount2 = 1 - discount2;
            double PandOneDis2 = price2 * oneMdiscount2;

            // 累加相关的值
            sum_qty += getdata(&Table, Table.quantity, a + 1);
            sum_base_price += price2;
            sum_discount += discount2;
            sum_disc_price += PandOneDis2;
            sum_charge += PandOneDis2 * (1 + getdata(&Table, Table.tax, a+1));
            count_order++; // 增加一个订单的数量
        }
    }
    // 处理剩余的元素，如果有的话
    for (; a < table_num; a++)
    {
        int date = getdata(&Table, Table.date, a);
        if (date <= n)          
        {
            price  = getdata(&Table, Table.price, a);
            discount = getdata(&Table, Table.discount, a);
            oneMdiscount = 1 - discount;
            PandOneDis = price * oneMdiscount;
            //tax = 

            sum_qty += getdata(&Table, Table.quantity, a);
            sum_base_price += price;
            sum_discount += discount;
            sum_disc_price += PandOneDis;
            sum_charge += PandOneDis * (1 + getdata(&Table, Table.tax, a));
            count_order++;
        }
    }
    SumQuantity = sum_qty;
    SumBasePrice = sum_base_price;
    SumDiscPrice = sum_disc_price;
    SumCharge = sum_charge;
    AvgQuantity = SumQuantity / table_num;
    AvgPrice = SumBasePrice / table_num;
    AvgDiscount = sum_discount / table_num;
    total = count_order;
}


// void calculate2(int n)      //经过循环展开的calculate1 因为加了simd反而不好
// {
//     long long sum_qty = 0, sum_base_price = 0;
//     double sum_disc_price = 0, sum_charge = 0, sum_discount = 0, avg_qty = 0;
//     double avg_price = 0, avg_disc = 0;     
//     size_t count_order = 0;
//     int table_num = Table.num;      
//     int price = 0;
//     double discount = 0;
//     double oneMdiscount = 0;
//     double PandOneDis = 0;
//     int price1 = 0;
//     double discount1 = 0;
//     double oneMdiscount1 = 0;
//     double PandOneDis1 = 0;
//     int price2 = 0;
//     double discount2 = 0;
//     double oneMdiscount2 = 0;
//     double PandOneDis2 = 0;
//     //double tax = 0;
//     // 2*2循环展开的思想是每次迭代处理两个元素，从而减少循环次数和循环控制的开销
//     // 为了保证正确性，需要考虑table_num是否为偶数，以及循环边界的处理
//     // 另外，为了避免重复计算，可以将一些常量和中间变量提取出来
//     int half_table_num = table_num / 2; // 计算table_num的一半，向下取整
//     //double one_plus_tax = 1 + getdata(&Table, Table.tax, 0); // 假设税率是固定的，只需获取一次
//     int a = 0; // 循环变量
//     // 处理前半部分的元素，每次两个
//     for (; a < half_table_num * 2; a += 2) 
//     {
//         int date1 = getdata(&Table, Table.date, a); // 获取第一个元素的日期
//         int date2 = getdata(&Table, Table.date, a + 1); // 获取第二个元素的日期
//         if (date1 <= n && date2 <= n) // 如果两个元素都满足条件
//         {
//             // 获取两个元素的价格和折扣，并计算相关的值
//             price1  = getdata(&Table, Table.price, a);
//             price2  = getdata(&Table, Table.price, a + 1);
//             discount1 = getdata(&Table, Table.discount, a);
//             discount2 = getdata(&Table, Table.discount, a + 1);
//             oneMdiscount1 = 1 - discount1;
//             oneMdiscount2 = 1 - discount2;
//             PandOneDis1 = price1 * oneMdiscount1;
//             PandOneDis2 = price2 * oneMdiscount2;
//            // 累加相关的值
//             sum_qty += getdata(&Table, Table.quantity, a) + getdata(&Table, Table.quantity, a + 1);
//             sum_base_price += price1 + price2;
//             sum_discount += discount1 + discount2;
//             sum_disc_price += PandOneDis1 + PandOneDis2;
//             sum_charge += PandOneDis1 * (1 + getdata(&Table, Table.tax, a)) 
//                         + PandOneDis2 * (1 + getdata(&Table, Table.tax, a+1));
//             count_order += 2; // 增加两个订单的数量
//         }
//         else if (date1 <= n) // 如果只有第一个元素满足条件
//         {
//             // 获取第一个元素的价格和折扣，并计算相关的值
//             int price1  = getdata(&Table, Table.price, a);
//             double discount1 = getdata(&Table, Table.discount, a);
//             double oneMdiscount1 = 1 - discount1;
//             double PandOneDis1 = price1 * oneMdiscount1;
//             // 累加相关的值
//             sum_qty += getdata(&Table, Table.quantity, a);
//             sum_base_price += price1;
//             sum_discount += discount1;
//             sum_disc_price += PandOneDis1;
//             sum_charge += PandOneDis1 * (1 + getdata(&Table, Table.tax, a));
//             count_order++; // 增加一个订单的数量
//         }
//         else if (date2 <= n) // 如果只有第二个元素满足条件
//         {
//             // 获取第二个元素的价格和折扣，并计算相关的值
//             int price2  = getdata(&Table, Table.price, a + 1);
//             double discount2 = getdata(&Table, Table.discount, a + 1);
//             double oneMdiscount2 = 1 - discount2;
//             double PandOneDis2 = price2 * oneMdiscount2;
//             // 累加相关的值
//             sum_qty += getdata(&Table, Table.quantity, a + 1);
//             sum_base_price += price2;
//             sum_discount += discount2;
//             sum_disc_price += PandOneDis2;
//             sum_charge += PandOneDis2 * (1 + getdata(&Table, Table.tax, a+1));
//             count_order++; // 增加一个订单的数量
//         }
//     }
//     // 处理剩余的元素，如果有的话
//     for (; a < table_num; a++)
//     {
//         int date = getdata(&Table, Table.date, a);
//         if (date <= n)          
//         {
//             price  = getdata(&Table, Table.price, a);
//             discount = getdata(&Table, Table.discount, a);
//             oneMdiscount = 1 - discount;
//             PandOneDis = price * oneMdiscount;
//             //tax = 
//             sum_qty += getdata(&Table, Table.quantity, a);
//             sum_base_price += price;
//             sum_discount += discount;
//             sum_disc_price += PandOneDis;
//             sum_charge += PandOneDis * (1 + getdata(&Table, Table.tax, a));
//             count_order++;
//         }
//     }
//     SumQuantity = sum_qty;
//     SumBasePrice = sum_base_price;
//     SumDiscPrice = sum_disc_price;
//     SumCharge = sum_charge;
//     AvgQuantity = SumQuantity / table_num;
//     AvgPrice = SumBasePrice / table_num;
//     AvgDiscount = sum_discount / table_num;
//     total = count_order;
// }


void calculate2(int n)      //未经过循环展开的simd算法  不如不加simd
{
    // 定义一些变量，用于存储累加和平均值的结果
    long long sum_qty = 0, sum_base_price = 0;
    double sum_disc_price = 0, sum_charge = 0, sum_discount = 0, avg_qty = 0;
    double avg_price = 0, avg_disc = 0;     
    size_t count_order = 0;
    int table_num = Table.num; // 获取表格的行数      
    int price = 0; // 用于存储每一行的价格
    double discount = 0; // 用于存储每一行的折扣
    double oneMdiscount = 0; // 用于存储1-折扣的值
    double PandOneDis = 0; // 用于存储价格乘以1-折扣的值
    //double tax = 0; // 用于存储每一行的税率，但是这里没有用到，所以注释掉了
    // 使用OpenMP的指令来开启并行区域，并指定共享变量和私有变量
    #pragma omp parallel shared(sum_qty, sum_base_price, sum_disc_price, sum_charge, sum_discount, count_order) private(price, discount, oneMdiscount, PandOneDis)
    {
        // 使用OpenMP的指令来对循环进行并行化，并指定循环变量、调度策略和归约操作
        #pragma omp for schedule(static) reduction(+:sum_qty, sum_base_price, sum_disc_price, sum_charge, sum_discount, count_order)
        for (int a = 0; a < table_num; a++) // 遍历表格的每一行
        {
            int date = getdata(&Table, Table.date, a); // 获取第a行的日期
            if (date <= n) // 如果日期小于等于n，说明符合条件          
            {
                price  = getdata(&Table, Table.price, a); // 获取第a行的价格
                discount = getdata(&Table, Table.discount, a); // 获取第a行的折扣
                oneMdiscount = 1 - discount; // 计算1-折扣的值
                PandOneDis = price * oneMdiscount; // 计算价格乘以1-折扣的值
                //tax = 
                sum_qty += getdata(&Table, Table.quantity, a); // 将第a行的数量累加到sum_qty中
                sum_base_price += price; // 将第a行的价格累加到sum_base_price中
                sum_discount += discount; // 将第a行的折扣累加到sum_discount中
                sum_disc_price += PandOneDis; // 将第a行的价格乘以1-折扣的值累加到sum_disc_price中
                sum_charge += PandOneDis * (1 + getdata(&Table, Table.tax, a)); // 将第a行的价格乘以1-折扣再乘以1+税率的值累加到sum_charge中
                count_order++; // 将符合条件的订单数量加一
            }
        }
    }
    // 将累加的结果赋值给全局变量
    SumQuantity = sum_qty;
    SumBasePrice = sum_base_price;
    SumDiscPrice = sum_disc_price;
    SumCharge = sum_charge;
    // 计算平均值，并赋值给全局变量
    AvgQuantity = SumQuantity / table_num;
    AvgPrice = SumBasePrice / table_num;
    AvgDiscount = sum_discount / table_num;
    // 将符合条件的订单数量赋值给全局变量
    total = count_order;
}

// void calculate2(int n)    //拥有循环展开的simd 效果很差，不如不改
// {
//     long long sum_qty = 0, sum_base_price = 0;
//     double sum_disc_price = 0, sum_charge = 0, sum_discount = 0, avg_qty = 0;
//     double avg_price = 0, avg_disc = 0;     
//     size_t count_order = 0;
//     int table_num = Table.num;      
//     int price = 0;
//     double discount = 0;
//     double oneMdiscount = 0;
//     double PandOneDis = 0;
//     //double tax = 0;
//     // 使用OpenMP的指令来开启并行区域，并指定共享变量和私有变量
//     #pragma omp parallel shared(sum_qty, sum_base_price, sum_disc_price, sum_charge, sum_discount, count_order) private(price, discount, oneMdiscount, PandOneDis)
//     {
//         // 使用OpenMP的指令来对循环进行并行化，并指定循环变量、调度策略和归约操作
//         #pragma omp for schedule(static) reduction(+:sum_qty, sum_base_price, sum_disc_price, sum_charge, sum_discount, count_order)
//         // 2*2循环展开的思想是每次迭代处理两个元素，从而减少循环次数和循环控制的开销
//         // 为了保证正确性，需要考虑table_num是否为偶数，以及循环边界的处理
//         // 另外，为了利用simd指令，需要将一些变量定义为__m128d类型，表示一个128位的向量，可以存储两个双精度浮点数
//         int half_table_num = table_num / 2; // 计算table_num的一半，向下取整
//         double one_plus_tax = 1 + getdata(&Table, Table.tax, 0); // 假设税率是固定的，只需获取一次
//         __m128d one_plus_tax_v = _mm_set1_pd(one_plus_tax); // 将税率转换为向量类型
//         int a = 0; // 循环变量
//         // 处理前半部分的元素，每次两个
//         for (; a < half_table_num * 2; a += 2) 
//         {
//             int date1 = getdata(&Table, Table.date, a); // 获取第一个元素的日期
//             int date2 = getdata(&Table, Table.date, a + 1); // 获取第二个元素的日期
//             if (date1 <= n && date2 <= n) // 如果两个元素都满足条件
//             {
//                 // 获取两个元素的价格和折扣，并转换为向量类型
//                 __m128d price_v  = _mm_set_pd(getdata(&Table, Table.price, a), getdata(&Table, Table.price, a + 1));
//                 __m128d discount_v = _mm_set_pd(getdata(&Table, Table.discount, a), getdata(&Table, Table.discount, a + 1));
//                 // 计算1-折扣的值和价格乘以1-折扣的值
//                 __m128d oneMdiscount_v = _mm_sub_pd(_mm_set1_pd(1), discount_v);
//                 __m128d PandOneDis_v = _mm_mul_pd(price_v, oneMdiscount_v);
//                 // 累加相关的值，使用simd指令进行加法和乘法
//                 sum_qty += getdata(&Table, Table.quantity, a) + getdata(&Table, Table.quantity, a + 1);
//                 sum_base_price += _mm_cvtsd_f64(_mm_hadd_pd(price_v, price_v)); // 使用水平加法指令将向量中的两个元素相加，然后转换为标量类型
//                 sum_discount += _mm_cvtsd_f64(_mm_hadd_pd(discount_v, discount_v));
//                 sum_disc_price += _mm_cvtsd_f64(_mm_hadd_pd(PandOneDis_v, PandOneDis_v));
//                 sum_charge += _mm_cvtsd_f64(_mm_hadd_pd(_mm_mul_pd(PandOneDis_v, _mm_set1_pd(1+getdata(&Table, Table.tax, a))), _mm_mul_pd(PandOneDis_v, _mm_set1_pd(1+getdata(&Table, Table.tax, a)))));
//                 count_order += 2; // 增加两个订单的数量
//             }
//             else if (date1 <= n) // 如果只有第一个元素满足条件
//             {
//                 // 获取第一个元素的价格和折扣，并计算相关的值
//                 price  = getdata(&Table, Table.price, a);
//                 discount = getdata(&Table, Table.discount, a);
//                 oneMdiscount = 1 - discount;
//                 PandOneDis = price * oneMdiscount;
//                 //tax = 
//                 // 累加相关的值
//                 sum_qty += getdata(&Table, Table.quantity, a);
//                 sum_base_price += price;
//                 sum_discount += discount;
//                 sum_disc_price += PandOneDis;
//                 sum_charge += PandOneDis * one_plus_tax;
//                 count_order++; // 增加一个订单的数量
//             }
//             else if (date2 <= n) // 如果只有第二个元素满足条件
//             {
//                 // 获取第二个元素的价格和折扣，并计算相关的值
//                 price  = getdata(&Table, Table.price, a + 1);
//                 discount = getdata(&Table, Table.discount, a + 1);
//                 oneMdiscount = 1 - discount;
//                 PandOneDis = price * oneMdiscount;
//                 //tax = 
//                 // 累加相关的值
//                 sum_qty += getdata(&Table, Table.quantity, a + 1);
//                 sum_base_price += price;
//                 sum_discount += discount;
//                 sum_disc_price += PandOneDis;
//                 sum_charge += PandOneDis * one_plus_tax;
//                 count_order++; // 增加一个订单的数量
//             }
//         }
//         // 处理剩余的元素，如果有的话
//         for (; a < table_num; a++)
//         {
//             int date = getdata(&Table, Table.date, a);
//             if (date <= n)          
//             {
//                 price  = getdata(&Table, Table.price, a);
//                 discount = getdata(&Table, Table.discount, a);
//                 oneMdiscount = 1 - discount;
//                 PandOneDis = price * oneMdiscount;
//                 //tax = 
//                 sum_qty += getdata(&Table, Table.quantity, a);
//                 sum_base_price += price;
//                 sum_discount += discount;
//                 sum_disc_price += PandOneDis;
//                 sum_charge += PandOneDis * (1 + getdata(&Table, Table.tax, a));
//                 count_order++;
//             }
//         }
//     }
//     SumQuantity = sum_qty;
//     SumBasePrice = sum_base_price;
//     SumDiscPrice = sum_disc_price;
//     SumCharge = sum_charge;
//     AvgQuantity = SumQuantity / table_num;
//     AvgPrice = SumBasePrice / table_num;
//     AvgDiscount = sum_discount / table_num;
//     total = count_order;
// }
