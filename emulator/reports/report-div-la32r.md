# 处理器运行报告
## 程序运行情况
|程序名|总指令数|总时钟数|IPC|
|---|---|---|---|
|div-la32r|144|390|0.369231|

## 分支预测（含预译码纠正）
### 整体情况
|总分支数|总预测正确数|总预测正确率|
|---|---|---|
|44|41|93.1818%|

### 各类指令预测
|分支类型|总分支数|总预测正确数|总预测正确率|
|---|---|---|---|
|**Branch**| 21 | 20 | 95.2381%|
|**JIRL**| 11 | 9 | 81.8182%|
|**BL**| 12 | 12 | 100%|

### 高速缓存命中
|高速缓存|访问次数|命中次数|命中率|
|---|---|---|---|
|**指令高速缓存**| 157 | 151 | 96.1783%|
|**数据高速缓存**| 35 | 32 | 91.4286%|
## 流水线阻塞
|阻塞原因|阻塞时钟数|阻塞率|
|---|---|---|
|**指令高速缓存缺失**| 217 | 55.641%|
|**数据高速缓存缺失**| 87 | 22.3077%|
|**取指队列满**| 15 | 3.84615%|
|**重命名空闲列表空**|0 | 0%|
|**重排序缓冲区满**|2 | 0.512821%|
|**第一算数发射队列满**|0 | 0%|
|**第二算数发射队列满**|0 | 0%|
|**乘除法发射队列满**|0 | 0%|
|**内存读写发射队列满**|36 | 9.23077%|
|**除法器运算**|0 | 0%|
|**写缓冲满**|9 | 2.30769%|

## 发射阶段
### 多发射率
|总发射数|发射率|单发射率|双发射率|三发射率|四发射率|
|---|---|---|---|---|---|---|
|129|33.0769%|56.5891%|34.8837%|8.52713%|0%|

### 各发射队列发射率
|发射队列名称|发射率|
|---|---|
|**第一算数发射队列**|16.1538%|
|**第二算数发射队列**|22.8205%|
|**乘除法发射队列**|1.79487%|
|**内存读写发射队列**|9.48718%|

## 提交阶段
|总提交数|提交率|1条提交率|2条提交率|3条提交率|4条提交率|
|---|---|---|---|---|---|
|105|26.9231%|62.8571%|37.1429%|0%|0%|
