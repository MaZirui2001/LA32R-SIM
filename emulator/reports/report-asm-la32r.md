# 处理器运行报告
## 程序运行情况
|程序名|总指令数|总时钟数|IPC|
|---|---|---|---|
|asm-la32r|41|143|0.286713|

## 分支预测（含预译码纠正）
### 整体情况
|总分支数|总预测正确数|总预测正确率|
|---|---|---|
|3|3|100%|

### 各类指令预测
|分支类型|总分支数|总预测正确数|总预测正确率|
|---|---|---|---|
|**Branch**| 1 | 1 | 100%|
|**JIRL**| 0 | 0 | 100%|
|**BL**| 2 | 2 | 100%|

### 高速缓存命中
|高速缓存|访问次数|命中次数|命中率|
|---|---|---|---|
|**指令高速缓存**| 44 | 40 | 90.9091%|
|**数据高速缓存**| 7 | 4 | 57.1429%|
## 流水线阻塞
|阻塞原因|阻塞时钟数|阻塞率|
|---|---|---|
|**指令高速缓存缺失**| 98 | 68.5315%|
|**数据高速缓存缺失**| 91 | 63.6364%|
|**取指队列满**| 0 | 0%|
|**重命名空闲列表空**|0 | 0%|
|**重排序缓冲区满**|0 | 0%|
|**第一算数发射队列满**|0 | 0%|
|**第二算数发射队列满**|0 | 0%|
|**算数分支发射队列满**|0 | 0%|
|**乘除法发射队列满**|0 | 0%|
|**内存读写发射队列满**|0 | 0%|
|**写缓冲满**|0 | 0%|

## 发射阶段
### 多发射率
|总发射数|发射率|单发射率|双发射率|三发射率|四发射率|五发射率|
|---|---|---|---|---|---|
|32|22.3776%|53.125%|9.375%|37.5%|0%|0%|

### 各发射队列发射率
|发射队列名称|发射率|
|---|---|
|**第一算数发射队列**|11.1888%|
|**第二算数发射队列**|10.4895%|
|**算数分支发射队列**|12.5874%|
|**乘除法发射队列**|0%|
|**内存读写发射队列**|6.99301%|

## 提交阶段
|总提交数|提交率|1条提交率|2条提交率|3条提交率|4条提交率|
|---|---|---|---|---|---|
|16|11.1888%|18.75%|31.25%|25%|25%|