# 处理器运行报告
## 程序运行情况
|程序名|总指令数|总时钟数|IPC|
|---|---|---|---|
|wanshu-la32r|2743|5822|0.471144|

## 分支预测（含预译码纠正）
### 整体情况
|总分支数|总预测正确数|总预测正确率|
|---|---|---|
|1318|1196|90.7436%|

### 各类指令预测
|分支类型|总分支数|总预测正确数|总预测正确率|
|---|---|---|---|
|**Branch**| 1309 | 1189 | 90.8327%|
|**JIRL**| 4 | 2 | 50%|
|**BL**| 5 | 5 | 100%|

### 高速缓存命中
|高速缓存|访问次数|命中次数|命中率|
|---|---|---|---|
|**指令高速缓存**| 4482 | 4476 | 99.8661%|
|**数据高速缓存**| 18 | 16 | 88.8889%|
## 流水线阻塞
|阻塞原因|阻塞时钟数|阻塞率|
|---|---|---|
|**指令高速缓存缺失**| 213 | 3.65854%|
|**数据高速缓存缺失**| 61 | 1.04775%|
|**取指队列满**| 1112 | 19.1%|
|**重命名空闲列表空**|0 | 0%|
|**重排序缓冲区满**|1234 | 21.1955%|
|**第一算数发射队列满**|0 | 0%|
|**第二算数发射队列满**|397 | 6.81896%|
|**乘除法发射队列满**|0 | 0%|
|**内存读写发射队列满**|12 | 0.206115%|
|**除法器运算**|3227 | 55.4277%|
|**写缓冲满**|127 | 2.18138%|

## 发射阶段
### 多发射率
|总发射数|发射率|单发射率|双发射率|三发射率|四发射率|
|---|---|---|---|---|---|---|
|3273|56.2178%|56.187%|38.069%|5.74397%|0%|

### 各发射队列发射率
|发射队列名称|发射率|
|---|---|
|**第一算数发射队列**|33.0814%|
|**第二算数发射队列**|38.5778%|
|**乘除法发射队列**|12.0577%|
|**内存读写发射队列**|0.360701%|

## 提交阶段
|总提交数|提交率|1条提交率|2条提交率|3条提交率|4条提交率|
|---|---|---|---|---|---|
|1865|32.0337%|52.9223%|47.0777%|0%|0%|
