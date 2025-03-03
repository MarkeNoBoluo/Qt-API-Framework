# Qt-API-Framework
![](C:\Users\wddkx\Desktop\Blog\博客文章管理\5.项目实战\QtAPI框架\设计图\Icon.webp)

A high-performance HTTP communication API management framework implemented on QNetwork.

- Base on QNetwork Module.

- high-performance HTTP Client.

- Easily customized for secondary development. 

- Unified management of various API interfaces.

- Asynchronous processing of response for each request.

- Support custom response message parsing.

  

## Supported platforms:

- [x] Windows (MSVC or MinGW)
- [x] Ubuntu 22.04.5 LTS
- [x] CentOS 7
- [x] Kylin v10 Sp1
- [x] Neo-Kylin v7


## The project architecture :

|     应用层 (Application)   |
|-----------------------------------|
| - 调用ResponseHandle实例完成API响应处理 |
| - 调用Service实例完成API请求 |

|     服务层 (Service)   |
|-----------------------------------|
| - VoteService（具体Api请求） |
| - VoteResponseHandle（具体Api请求响应处理） |

|    核心层 (Core)       |
|-----------------------------------|
| - HttpApiManager（API管理） |
| - HttpRequestManager（HTTP客户端） |
| - ApiServiceBase（请求服务基类） |
| - ApiResponseHandler（响应处理基类） |

|    网络层 (Network)      |
|-----------------------------------|
| - QNetworkAccessManager     |
| - SSL配置            |
| - 连接池管理           |

## Project Flow Chart

![](C:\Users\wddkx\Desktop\Blog\博客文章管理\5.项目实战\QtAPI框架\流程图\Flow Chart.png)

## Quick start

1. First clone the repository:

​	```git clone  https://github.com/MarkeNoBoluo/Qt-API-Framework.git```

2. Copy into your project.

3. Inherit ApiServiceBase to implement your API service layer module.

4. Inherit ApiResponseHandle to implement your API response hanlde module.

5. Use it:

   ``` VoteServiceHandler h;//handle instance```

   ``` VoteService v;//service request instance```

   ``` v.setResponseHandler(&h);//bind handle to service request```

   ```     v.updateAllVoteItem({});//specific request ```

