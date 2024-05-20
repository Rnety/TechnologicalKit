# **1**、简介

Apache Shiro 是 Java 的一个安全框架。目前，使用 Apache Shiro 的人越来越多，因为它相当简单，对比 Spring Security，可能没有 Spring Security 做的功能强大。

> Shiro 可以进阶到 Spring Security

但是在实际工作时可能并不需要那么复杂的东西，所以使用小而简单的 Shiro 就足够了。对于它俩到底哪个好，这个不必纠结，能更简单的解决项目问题就好了。

Shiro 可以帮助我们完成：认证、授权、加密、会话管理、与 Web 集成、缓存等。而且 Shiro 的 API 也是非常简单；其基本功能点如下图所示：

![image-20211113144336464](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211113144336464.png)





> API，英文全称Application Programming Interface，翻译为“应用程序编程接口”。 是一些预先定义的函数，目的是提供应用程序与开发人员基于某软件或硬件得以访问一组例程的能力，而又无需访问源码，或理解内部工作机制的细节

- **Authentication**：身份认证 / 登录，验证用户是不是拥有相应的身份；
- **Authorization**：授权，即权限验证，验证某个已认证的用户是否拥有某个权限；即判断用户是否能做事情，常见的如：验证某个用户是否拥有某个角色。或者细粒度的验证某个用户对某个资源是否具有某个权限；
- **Session** **Management**：会话管理，即用户登录后就是一次会话，在没有退出之前，它的所有信息都在会话中；会话可以是普通 JavaSE 环境的，也可以是如 Web 环境的；
- **Cryptography**：加密，保护数据的安全性，如密码加密存储到数据库，而不是明文存储；
- **Web Support**：Web 支持，可以非常容易的集成到 Web 环境；
- **Caching**：缓存，比如用户登录后，其用户信息、拥有的角色 / 权限不必每次去查，这样可以提高效率；
- **Concurrency**：shiro 支持多线程应用的并发验证，即如在一个线程中开启另一个线程，能把权限自动传播过去；
- **Testing**：提供测试支持；
- **Run As**：允许一个用户假装为另一个用户（如果他们允许）的身份进行访问；
- **Remember Me**：记住我，这个是非常常见的功能，即一次登录后，下次再来的话不用登录了。

**记住一点，Shiro 不会去维护用户、维护权限；这些需要我们自己去设计 / 提供；然后通过相应的接口注入给 Shiro 即可。**

接下来我们分别从外部和内部来看看 Shiro 的架构，对于一个好的框架，从外部来看应该具有非常简单易于使用的 API，且 API 契约明确；从内部来看的话，其应该有一个可扩展的架构，即非常容易插入用户自定义实现，因为任何框架都不能满足所有需求。

首先，我们从外部来看 Shiro 吧，即从应用程序角度的来观察如何使用 Shiro 完成工作。如下图：

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/2.png)

可以看到：应用代码直接交互的对象是 Subject，也就是说 Shiro 的对外 API 核心就是 Subject；其每个 API 的含义：

**Subject**：主体，代表了当前 “用户”，这个用户不一定是一个具体的人，与当前应用交互的任何东西都是 Subject，如网络爬虫，机器人等；即一个抽象概念；所有 Subject 都绑定到 SecurityManager，与 Subject 的所有交互都会委托给 SecurityManager；可以把 Subject 认为是一个门面；SecurityManager 才是实际的执行者；

**SecurityManager**：安全管理器；即所有与安全有关的操作都会与 SecurityManager 交互；且它管理着所有 Subject；可以看出它是 Shiro 的核心，它负责与后边介绍的其他组件进行交互，如果学习过 SpringMVC，你可以把它看成 DispatcherServlet 前端控制器；

**Realm**：域，Shiro 从 Realm 获取安全数据（如用户、角色、权限），就是说 SecurityManager 要验证用户身份，那么它需要从 Realm 获取相应的用户进行比较以确定用户身份是否合法；也需要从 Realm 得到用户相应的角色 / 权限进行验证用户是否能进行操作；可以把 Realm 看成 DataSource，即安全数据源。

**也就是说对于我们而言，最简单的一个 Shiro 应用：**

1. **应用代码通过 Subject 来进行认证和授权，而 Subject 又委托给 SecurityManager；**
2. **我们需要给 Shiro 的 SecurityManager 注入 Realm，从而让 SecurityManager 能得到合法的用户及其权限进行判断。**

**从以上也可以看出，Shiro 不提供维护用户 / 权限，而是通过 Realm 让开发人员自己注入。**

接下来我们来从 Shiro 内部来看下 Shiro 的架构，如下图所示：

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/3.png)

- **Subject**：主体，可以看到主体可以是任何可以与应用交互的 “用户”；
- **SecurityManager**：相当于 SpringMVC 中的 DispatcherServlet 或者 Struts2 中的 FilterDispatcher；是 Shiro 的心脏；所有具体的交互都通过 SecurityManager 进行控制；它管理着所有 Subject、且负责进行认证和授权、及会话、缓存的管理。
- **Authenticator**：认证器，负责主体认证的，这是一个扩展点，如果用户觉得 Shiro 默认的不好，可以自定义实现；其需要认证策略（Authentication Strategy），即什么情况下算用户认证通过了；
- **Authorizer**：授权器，或者访问控制器，用来决定主体是否有权限进行相应的操作；即控制着用户能访问应用中的哪些功能；
- **Realm**：可以有 1 个或多个 Realm，可以认为是安全实体数据源，即用于获取安全实体的；可以是 JDBC 实现，也可以是 LDAP 实现，或者内存实现等等；由用户提供；注意：Shiro 不知道你的用户 / 权限存储在哪及以何种格式存储；所以我们一般在应用中都需要实现自己的 Realm；
- **SessionManager**：如果写过 Servlet 就应该知道 Session 的概念，Session 呢需要有人去管理它的生命周期，这个组件就是 SessionManager；而 Shiro 并不仅仅可以用在 Web 环境，也可以用在如普通的 JavaSE 环境、EJB 等环境；所以呢，Shiro 就抽象了一个自己的 Session 来管理主体与应用之间交互的数据；这样的话，比如我们在 Web 环境用，刚开始是一台 Web 服务器；接着又上了台 EJB 服务器；这时想把两台服务器的会话数据放到一个地方，这个时候就可以实现自己的分布式会话（如把数据放到 Memcached 服务器）；
- **SessionDAO**：DAO 大家都用过，数据访问对象，用于会话的 CRUD，比如我们想把 Session 保存到数据库，那么可以实现自己的 SessionDAO，通过如 JDBC 写到数据库；比如想把 Session 放到 Memcached 中，可以实现自己的 Memcached SessionDAO；另外 SessionDAO 中可以使用 Cache 进行缓存，以提高性能；
- **CacheManager**：缓存控制器，来管理如用户、角色、权限等的缓存的；因为这些数据基本上很少去改变，放到缓存中后可以提高访问的性能
- **Cryptography**：密码模块，Shiro 提供了一些常见的加密组件用于如密码加密 / 解密的。

# 2、Shrio的身份验证

## 身份验证

**身份验证**，即在应用中谁能证明他就是他本人。一般提供如他们的身份 ID 一些标识信息来表明他就是他本人，如提供身份证，用户名 / 密码来证明。

在 shiro 中，用户需要提供 `principals` （身份）和 `credentials`（证明）给 shiro，从而应用能验证用户身份：

**principals**：身份，即主体的标识属性，可以是任何东西，如用户名、邮箱等，唯一即可。一个主体可以有多个 `principals`，但只有一个 `Primary principals`，一般是用户名 / 密码 / 手机号。

**credentials**：证明 / 凭证，即只有主体知道的安全值，如密码 / 数字证书等。

最常见的 `principals` 和 `credentials` 组合就是用户名 / 密码了。接下来先进行一个基本的身份认证。

另外两个相关的概念是之前提到的 **`Subject`** 及 **`Realm`**，分别是主体及验证主体的数据源。

## 环境准备

本文使用 `Maven` 构建，因此需要一点 `Maven` 知识。首先准备环境依赖： 

```xml
<dependencies>
    <dependency>
        <groupId>junit</groupId>
        <artifactId>junit</artifactId>
        <version>4.13.2</version>
    </dependency>
    <dependency>
        <groupId>commons-logging</groupId>
        <artifactId>commons-logging</artifactId>
        <version>1.1.3</version>
    </dependency>
    <dependency>
        <groupId>org.apache.shiro</groupId>
        <artifactId>shiro-core</artifactId>
        <version>1.5.3</version>
    </dependency>
</dependencies>
```

添加 `junit`、`common-logging` 及 `shiro-core` 依赖即可。

## 登录 / 退出

1、首先准备一些用户身份 / 凭据（shiro.ini）

```ini
[users]
zhang=123
wang=123
```

此处使用 ini 配置文件，通过 [users] 指定了两个主体：zhang/123、wang/123。

> 1、.ini 文件是Initialization File的缩写，即初始化文件，是windows的系统配置文件所采用的存储格式
> 2、shiro的配置文件都是以.ini结尾i的配置文件，在但shiro项目中我们把配置文件放在项目的resource文件夹下即可
> 3、ini配置文件用来学习shiro书写我们系统中相关权限数据

2、测试用例（com.github.zhangkaitao.shiro.chapter2.LoginLogoutTest）

```java
@Test
public void testHelloworld() {
    //1、创造安全管理对象
	DefaultSecurityManager securityManager = new DefaultSecurityManager();
	//2.给安全管理器设置realm
	securityManager.setRealm(new IniRealm("classpath:shiro.ini"));
	//3.securityUtils给全局安全工具类设置安装管理器
	SecurityUtils.setSecurityManager(securityManager);
	//4.关键对象subject 主体
	Subject subject = SecurityUtils.getSubject();
	//5.创建令牌
	UsernamePasswordToken token = new UsernamePasswordToken("zhang","123");
    try {
        //4、登录，即身份验证
      System.out.println("认证状态"+subject.isAuthenticated());
	  subject.login(token);
	  System.out.println("认证状态"+subject.isAuthenticated());
    } catch (AuthenticationException e) {
        //5、身份验证失败
      e.printStackTrace();
    }
    Assert.assertEquals(true, subject.isAuthenticated()); //断言用户已经登录
    //6、退出
    subject.logout();
}
```

- 首先通过 `new IniSecurityManagerFactory` 并指定一个 `ini` 配置文件来创建一个 `SecurityManager` 工厂；
- 接着获取 `SecurityManager` 并绑定到 `SecurityUtils`，这是一个全局设置，设置一次即可；
- 通过 `SecurityUtils` 得到 `Subject`，其会自动绑定到当前线程；如果在 web 环境在请求结束时需要解除绑定；然后获取身份验证的 `Token`，如用户名 / 密码；
- 调用 `subject.login` 方法进行登录，其会自动委托给 `SecurityManager.login` 方法进行登录；
- 如果身份验证失败请捕获 `AuthenticationException` 或其子类，常见的如： `DisabledAccountException`（禁用的帐号）、`LockedAccountException`（锁定的帐号）、`UnknownAccountException`（错误的帐号）、`ExcessiveAttemptsException`（登录失败次数过多）、`IncorrectCredentialsException` （错误的凭证）、`ExpiredCredentialsException`（过期的凭证）等，具体请查看其继承关系；对于页面的错误消息展示，最好使用如 “用户名 / 密码错误” 而不是 “用户名错误”/“密码错误”，防止一些恶意用户非法扫描帐号库；
- 最后可以调用 `subject.logout` 退出，其会自动委托给 `SecurityManager.logout` 方法退出。

![image-20211113152443628](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211113152443628.png)

**从如上代码可总结出身份验证的步骤**：

1. 收集用户身份 / 凭证，即如用户名 / 密码；
2. 调用 `Subject.login` 进行登录，如果失败将得到相应的 `AuthenticationException` 异常，根据异常提示用户错误信息；否则登录成功；
3. 最后调用 `Subject.logout` 进行退出操作。

如上测试的几个问题：

1. 用户名 / 密码硬编码在 `ini` 配置文件，以后需要改成如数据库存储，且密码需要加密存储；
2. 用户身份 `Token` 可能不仅仅是用户名 / 密码，也可能还有其他的，如登录时允许用户名 / 邮箱 / 手机号同时登录。

## 身份认证流程

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/4.png)

流程如下：

1. 首先调用 `Subject.login(token)` 进行登录，其会自动委托给 `Security Manager`，调用之前必须通过 `SecurityUtils.setSecurityManager()` 设置；

2. `SecurityManager` 负责真正的身份验证逻辑；它会委托给 `Authenticator` 进行身份验证；

3. **`Authenticator` 才是真正的身份验证者，`Shiro API` 中核心的身份认证入口点，此处可以自定义插入自己的实现**；

4. `Authenticator` 可能会委托给相应的 `AuthenticationStrategy` 进行多 `Realm` 身份验证，默认 `ModularRealmAuthenticator` 会调用 `AuthenticationStrategy` 进行多 `Realm` 身份验证；

5. **`Authenticator `会把相应的 `token` 传入 `Realm`，从 `Realm` 获取身份验证信息**，如果没有返回 / 抛出异常表示身份验证成功了。此处可以配置多个 `Realm`，将按照相应的顺序及策略进行访问。

![image-20211113153124300](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211113153124300.png)

下面讲介绍`AuthorizingRealm `类中验证的**主方法**

```java

  public final AuthenticationInfo getAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
    AuthenticationInfo info = this.getCachedAuthenticationInfo(token); 
    if (info == null) {
      info = this.doGetAuthenticationInfo(token);  
      log.debug("Looked up AuthenticationInfo [{}] from doGetAuthenticationInfo", info);
      if (token != null && info != null) {
        this.cacheAuthenticationInfoIfPossible(token, info);
      }
    } else {
      log.debug("Using cached authentication info [{}] to perform credentials matching.", info);
    }

    if (info != null) {
      this.assertCredentialsMatch(token, info);
    } else {
      log.debug("No AuthenticationInfo found for submitted AuthenticationToken [{}].  Returning null.", token);
    }
```

**1、第一步取缓存中获取AuthenticationInfo**

```java
  private AuthenticationInfo getCachedAuthenticationInfo(AuthenticationToken token) {
    AuthenticationInfo info = null;
    Cache<Object, AuthenticationInfo> cache = this.getAvailableAuthenticationCache();
    if (cache != null && token != null) {
      log.trace("Attempting to retrieve the AuthenticationInfo from cache.");
      Object key = this.getAuthenticationCacheKey(token);
      info = (AuthenticationInfo)cache.get(key);
      if (info == null) {
        log.trace("No AuthorizationInfo found in cache for key [{}]", key);
      } else {
        log.trace("Found cached AuthorizationInfo for key [{}]", key);
      }
    }

    return info;
  }
```

**设置AuthenticationInfo为空并获得Shiro的Cache中所有的AuthenticationInfo**

- 当Cache不为空（即有对应的缓存）且token不为空（即有对应的传入值时候），会查找是否在Cache有对应token的信息（不用数据库再查一次）并返还AuthenticationInfo。
- 当当Cache为空（即无有对应的缓存）或token为空（没有传入值的时候，这种情况几乎不可能），则返回一个空的AuthenticationInfo

**2、如果缓存中没有数据则使用`doGetAuthenticationInfo`方法获得数据库数据，并把对应的信息存入Cache中存入（info）**

该方法是抽象的当我们继承于`AuthorizingRealm`时候自己来编写

```java
  protected abstract AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken var1) throws AuthenticationException;
}
```

**3、验证密码，如果我们的Cache里面有对应的AuthenticationInfo我们从Cache里面进行验证；没有则在数据库查询以后再放入Cache中（info）**

> 我们只需要重写doGetAuthenticationInfo方法即可，返回对应的数据库的UserId和password，接下来的密码的查询由Shiro帮助我们完成，是封装好的

## Realm

Realm：域，`Shiro` 从 `Realm `获取安全数据（如用户、角色、权限），就是说 `SecurityManager` 要验证用户身份，那么它需要从 `Realm` 获取相应的用户进行比较以确定用户身份是否合法；也需要从 `Realm` 得到用户相应的角色 / 权限进行验证用户是否能进行操作；**可以把 `Realm` 看成 `DataSource`，即安全数据源**。如我们之前的 `ini` 配置方式将使用 `org.apache.shiro.realm.text.IniRealm`。

> 之前我们是通过初始化文件ini来设置我们的数据源，现在我们是数据库来查询我们的的信息，来保证我们的安全数据源。

**单 `Realm` 配置**

1、自定义 `Realm` 实现：

```java
public class MyRealm1 implements AuthorizingRealm {
    /**当我们整合其他框架的，如jwt，我们的token就是JwtToken类型的。
		我们这里的supports就算要改写成 return token instanceof JwtToken; 
    @Override
    public boolean supports(AuthenticationToken token) {
        //仅支持UsernamePasswordToken类型的Token
        return token instanceof UsernamePasswordToken; 
    }**/
    @Override
 	protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principalCollection) {
     //自定义对应的权限认证   
	return null;
  }
    @Override
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        String username = (String)token.getPrincipal();  //得到用户名
        String password = new String((char[])token.getCredentials()); //得到密码
        if(!"zhang".equals(username)) {
            throw new UnknownAccountException(); //如果用户名错误
        }
        if(!"123".equals(password)) {
            throw new IncorrectCredentialsException(); //如果密码错误
        }
        //如果身份认证验证成功，返回一个AuthenticationInfo实现；
        //public SimpleAuthenticationInfo(Object principal, Object hashedCredentials, ByteSource credentialsSalt, String realmName)可以有四个参数
        //参数一：数据库用户名 
        //参数二：数据库用户对应密码 
        //参数三：ByteSource.Util.bytes(String str)注册时候的随机盐推荐在数据库里面的取 
        //参数四：Realm名字
        return new SimpleAuthenticationInfo(username, password, getName());
    }
}
```

>`supports(AuthenticationToken token)`是我们需要重写方法中只支持我们的`UsernamePasswordToken`类型的token，在整合其他框架的时候，我们需要返回自己的token

![image-20211117002957550](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211117002957550.png)

2、对应的testHelloworld()里面的`securityManager.setRealm`也要进行改写

```java
securityManager.setRealm(new MyRealm1());
```

**多 `Realm` 配置**

1、因为我们的方法有`public void setRealms(Collection<Realm> realms)`所以当我们有多个realm的时候，我们可以先放进一个Collection<Realm>集合里面，再把该集合放进这个参数里面

```java
@Test
public void testHelloworld() {
    //1、创造安全管理对象
	DefaultSecurityManager securityManager = new DefaultSecurityManager();
	//2.给安全管理器设置Realm
     Collection<Realm> collection = new ArrayList<>();
    //3.假设我们有多重Realm,如Realm
    collection.add(new Realm1());
    collection.add(new Realm2());
    //.....
	securityManager.setRealm(collection);
	//......
}
```

**`securityManager` 会按照 `realms` 指定的顺序进行身份认证。**

- 在基础学习的ini文件中，我们使用显示指定顺序的方式指定了 `Realm` 的顺序，如果删除 “securityManager.realms=$myRealm1,$myRealm2”，那么`securityManager` 会按照 `realm` 声明的顺序进行使用（即无需设置 `realms` 属性，其会自动发现），当我们显示指定 `realm` 后，其他没有指定 `realm` 将被忽略，如 “securityManager.realms=$myRealm1”，那么 `myRealm2` 不会被自动设置进去。
- 我们上面的写法也具有相同的思路

> 多重Realm的方式，让我们可以通过不同的方式进行用户的认证
> 简单的说：可以用电话登入，也可以用邮箱登入，也可以用身份证登入等等

**`Shiro` 默认提供的 `Realm`**

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/5.png)

> 1、我们的principals在**`SimpleAccountRealm`**的`doGetAuthenticationInfo`在这个方法中完成用户名校验
> 2、我们的credentials在**`AuthenticatingRealm`**中的`assertCredentialsMatch`在这个方法中完成密码校验
>
> 3、在**`AuthenticatingRealm`** 用**`doGetAuthenticationInfo`**方法来认证realm
> 4、在**`AuthorizingRealm`**用 **`doGetAuthorizationInfo`**方法来授权realm

**以后一般继承 `AuthorizingRealm`（授权）即可**；其继承了 `AuthenticatingRealm`（即身份验证），而且也间接继承了 `CachingRealm`（带有缓存实现）。其中主要默认实现如下：

**org.apache.shiro.realm.text.IniRealm**：[users] 部分指定用户名 / 密码及其角色；[roles] 部分指定角色即权限信息；

**org.apache.shiro.realm.text.PropertiesRealm**： user.username=password,role1,role2 指定用户名 / 密码及其角色；role.role1=permission1,permission2 指定角色及权限信息；

**org.apache.shiro.realm.jdbc.JdbcRealm**：通过 sql 查询相应的信息，如 “select password from users where username = ?” 获取用户密码，“select password, password_salt from users where username = ?” 获取用户密码及密码字段；“select role_name from user_roles where username = ?” 获取用户角色；“select permission from roles_permissions where role_name = ?” 获取角色对应的权限信息；也可以调用相应的 api 进行自定义 sql；

**JDBC Realm 使用**

1、数据库及依赖

```xml
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>5.1.25</version>
        </dependency>
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid</artifactId>
            <version>0.2.23</version>
        </dependency>
```

本文将使用 mysql 数据库及 druid 连接池；

2、到数据库 shiro 下建三张表：`users`（用户名 / 密码）、`user_roles`（用户 / 角色）、`roles_permissions`（角色 / 权限），具体请参照 shiro-example-chapter2/sql/shiro.sql；并添加一个用户记录，用户名 / 密码为 zhang/123；

3、`ini` 配置`（shiro-jdbc-realm.ini）`

```ini
#自定义的Realm
jdbcRealm=org.apache.shiro.realm.jdbc.JdbcRealm
#数据源
dataSource=com.alibaba.druid.pool.DruidDataSource
#数据源对应配置
dataSource.driverClassName=com.mysql.jdbc.Driver
dataSource.url=jdbc:mysql://localhost:3306/shiro
dataSource.username=root
#dataSource.password=
#设置Realm的数据源
jdbcRealm.dataSource=$dataSource
#指定securityManager的realms实现
securityManager.realms=$jdbcRealm
```

1. 变量名 = 全限定类名会自动创建一个类实例
2. 变量名. 属性 = 值 自动调用相应的 `setter` 方法进行赋值
3. $ 变量名 引用之前的一个对象实例
4. 测试代码请参照` com.github.zhangkaitao.shiro.chapter2.LoginLogoutTest` 的 `testJDBCRealm` 方法，和之前的没什么区别。

## Authenticator 及 AuthenticationStrategy

Authenticator 的职责是验证用户帐号，是 Shiro API 中身份验证核心的入口点：

```java
public AuthenticationInfo authenticate(AuthenticationToken authenticationToken)
            throws AuthenticationException;
```

如果验证成功，将返回 `AuthenticationInfo` 验证信息；

- 此信息中包含了身份及凭证
- 如果验证失败将抛出相应的 `AuthenticationException` 实现。

`SecurityManager`接口继承了 `Authenticator`，另外还有一个 `ModularRealmAuthenticator` 实现，其委托给多个 `Realm` 进行验证，验证规则通过 `AuthenticationStrategy` 接口指定，默认提供的实现：

**`FirstSuccessfulStrategy`**：只要有一个 `Realm` 验证成功即可，只返回第一个 `Realm` 身份验证成功的认证信息，其他的忽略；

**`AtLeastOneSuccessfulStrategy/`**：只要有一个 `Realm` 验证成功即可，和 `FirstSuccessfulStrategy` 不同，返回所有 `Realm` 身份验证成功的认证信息；

**`AllSuccessfulStrategy`**：所有 `Realm` 验证成功才算成功，且返回所有 `Realm` 身份验证成功的认证信息，如果有一个失败就失败了。

`ModularRealmAuthenticator` 默认使用 `AtLeastOneSuccessfulStrategy` 策略。

假设我们有三个` realm`：
`myRealm1`： 用户名 / 密码为 zhang/123 时成功，且返回身份 / 凭据为 zhang/123；
`myRealm2`： 用户名 / 密码为 wang/123 时成功，且返回身份 / 凭据为 wang/123；
`myRealm3`： 用户名 / 密码为 zhang/123 时成功，且返回身份 / 凭据为 zhang@163.com/123，和 myRealm1 不同的是返回时的身份变了；

1、ini 配置文件 (shiro-authenticator-all-success.ini)

```ini
#指定securityManager的authenticator实现
authenticator=org.apache.shiro.authc.pam.ModularRealmAuthenticator
securityManager.authenticator=$authenticator
#指定securityManager.authenticator的authenticationStrategy
allSuccessfulStrategy=org.apache.shiro.authc.pam.AllSuccessfulStrategy
securityManager.authenticator.authenticationStrategy=$allSuccessfulStrategy
myRealm1=com.github.zhangkaitao.shiro.chapter2.realm.MyRealm1
myRealm2=com.github.zhangkaitao.shiro.chapter2.realm.MyRealm2
myRealm3=com.github.zhangkaitao.shiro.chapter2.realm.MyRealm3
securityManager.realms=$myRealm1,$myRealm3
```

2、测试代码（com.github.zhangkaitao.shiro.chapter2.AuthenticatorTest）

- 首先通用化登录逻辑

```java
    private void login(String configFile) {
        //1、获取SecurityManager工厂，此处使用Ini配置文件初始化SecurityManager
        Factory<org.apache.shiro.mgt.SecurityManager> factory =
                new IniSecurityManagerFactory(configFile);
        //2、得到SecurityManager实例 并绑定给SecurityUtils
        org.apache.shiro.mgt.SecurityManager securityManager = factory.getInstance();
        SecurityUtils.setSecurityManager(securityManager);
        //3、得到Subject及创建用户名/密码身份验证Token（即用户身份/凭证）
        Subject subject = SecurityUtils.getSubject();
        UsernamePasswordToken token = new UsernamePasswordToken("zhang", "123");
        subject.login(token);
    }
```

- 测试` AllSuccessfulStrategy` 成功：

```java
    @Test
    public void testAllSuccessfulStrategyWithSuccess() {
        login("classpath:shiro-authenticator-all-success.ini");
        Subject subject = SecurityUtils.getSubject();
        //得到一个身份集合，其包含了Realm验证成功的身份信息
        PrincipalCollection principalCollection = subject.getPrincipals();
        Assert.assertEquals(2, principalCollection.asList().size());
    }
```

即 `PrincipalCollection` 包含了 zhang 和 zhang@163.com 身份信息。

- 测试 `AllSuccessfulStrategy` 失败：

```java
    @Test(expected = UnknownAccountException.class)
    public void testAllSuccessfulStrategyWithFail() {
        login("classpath:shiro-authenticator-all-fail.ini");
        Subject subject = SecurityUtils.getSubject();
}
```

`shiro-authenticator-all-fail.ini` 与` shiro-authenticator-all-success.ini` 不同的配置是使用了 `securityManager.realms=$myRealm1，$myRealm2`；即 `myRealm` 验证失败。

对于 `AtLeastOneSuccessfulStrategy` 和 `FirstSuccessfulStrategy` 的区别，请参照 `testAtLeastOneSuccessfulStrategyWithSuccess` 和 `testFirstOneSuccessfulStrategyWithSuccess` 测试方法。唯一不同点一个是返回所有验证成功的 `Realm` 的认证信息；另一个是只返回第一个验证成功的 `Realm` 的认证信息。

自定义 `AuthenticationStrategy` 实现，首先看其 `API`：

```java
//在所有Realm验证之前调用
AuthenticationInfo beforeAllAttempts(
Collection<? extends Realm> realms, AuthenticationToken token) 
throws AuthenticationException;
//在每个Realm之前调用
AuthenticationInfo beforeAttempt(
Realm realm, AuthenticationToken token, AuthenticationInfo aggregate) 
throws AuthenticationException;
//在每个Realm之后调用
AuthenticationInfo afterAttempt(
Realm realm, AuthenticationToken token, 
AuthenticationInfo singleRealmInfo, AuthenticationInfo aggregateInfo, Throwable t)
throws AuthenticationException;
//在所有Realm之后调用
AuthenticationInfo afterAllAttempts(
AuthenticationToken token, AuthenticationInfo aggregate) 
throws AuthenticationException;
```

因为每个 `AuthenticationStrategy` 实例都是无状态的，所有每次都通过接口将相应的认证信息传入下一次流程；通过如上接口可以进行如合并 / 返回第一个验证成功的认证信息。

自定义实现时一般继承 `org.apache.shiro.authc.pam.AbstractAuthenticationStrategy` 即可，具体可以参考代码 `com.github.zhangkaitao.shiro.chapter`2.`authenticator.strategy` 包下 `OnlyOneAuthenticatorStrategy` 和` AtLeastTwoAuthenticatorStrategy`。

# 3、Shiro 授权

## 授权

授权，也叫访问控制，**即在应用中控制谁能访问哪些资源（如访问页面/编辑数据/页面操作等）**。

在授权中需了解的几个关键对象：**主体（Subject）、资源（Resource）、权限（Permission）、角色（Role）**。

- 主体：主体，即访问应用的用户，在 Shiro 中使用 Subject 代表该用户。用户只有授权后才允许访问相应的资源。

- 资源：在应用中用户可以访问的URL，比如访问 JSP 页面、查看/编辑某些数据、访问某个业务方法、打印文本等等都是资源。用户只要授权后才能访问。

- 权限：安全策略中的原子授权单位，通过权限我们可以表示在应用中用户有没有操作某个资源的权力。**即权限表示在应用中用户能不能访问某个资源，如： 访问用户列表页面 查看/新增/修改/删除用户数据（即很多时候都是 CRUD（增查改删）式权限控制）打印文档等**。如上可以看出，权限代表了用户有没有操作某个资源的权利，即反映在某个资源上的操作允不允许，不反映谁去执行这个操作。所以后续还需要把权限赋予给用户，即定义哪个用户允许在某个资源上做什么操作（权限），Shiro 不会去做这件事情，而是由实现人员提供。

**Shiro 支持粗粒度权限（如用户模块的所有权限）和细粒度权限（操作某个用户的权限，即实例级别的），后续部分介绍。**

- 角色：角色代表了操作集合，可以理解为权限的集合，**一般情况下我们会赋予用户角色而不是权限，即这样用户可以拥有一组权限，赋予权限时比较方便**。典型的如：项目经理、技术总监、CTO、开发工程师等都是角色，不同的角色拥有一组不同的权限。

- 隐式角色： 即直接通过角色来验证用户有没有操作权限，如在应用中 CTO、技术总监、开发工程师可以使用打印机，假设某天不允许开发工程师使用打印机，此时需要从应用中删除相应代码；再如在应用中 CTO、技术总监可以查看用户、查看权限；突然有一天不允许技术总监查看用户、查看权限了，需要在相关代码中把技术总监角色从判断逻辑中删除掉；即粒度是以角色为单位进行访问控制的，粒度较粗；如果进行修改可能造成多处代码修改。

- 显示角色： 在程序中通过权限控制谁能访问某个资源，角色聚合一组权限集合；这样假设哪个角色不能访问某个资源，只需要从角色代表的权限集合中移除即可；无须修改多处代码；即粒度是以资源/实例为单位的；粒度较细。

请 google 搜索“RBAC”和“RBAC新解”分别了解“基于角色的访问控制”“基于资源的访问控制(Resource-Based Access Control)”。

## 授权方式

- 基于角色的访问控制

  -  RBAC基于角色的访问控制(Role-Based Access Control)是以角色为中心进行访问控制

    ```java
    if(subject.hasRole("admin")){
        //操作说明资源
    }
    ```

    

- 基于资源的访问控制

  -  RBAC基于资源的访问控制(Resource-Based Access Control)是以资源为中心进行访问控制

    ```java
    if(subject.isPermission("user:update:01")){
        //对01用户进行更新
    }
    if(subject.isPermission("user:update:*")){
        //对用户进行更新
    }
    ```

    

## shiro授权方式

Shiro 支持三种方式的授权：

编程式：通过写 if/else 授权代码块完成：

```java
Subject subject = SecurityUtils.getSubject();
if(subject.hasRole(“admin”)) {
    //有权限
} else {
    //无权限
}
```

注解式：通过在执行的 Java 方法上放置相应的注解完成：

```java
@RequiresRoles("admin")
public void hello() {
    //有权限
}
```

没有权限将抛出相应的异常；

JSP/GSP 标签：在 JSP/GSP 页面通过相应的标签完成：

```jsp
<shiro:hasRole name="admin">
<!— 有权限 —>
</shiro:hasRole>
```

后续部分将详细介绍如何使用。

## 授权

**基于角色的访问控制（隐式角色）**

1、在 ini 配置文件配置用户拥有的角色（shiro-role.ini）

```ini
[users]
zhang=123,role1,role2
wang=123,role1
```

规则即：“用户名=密码,角色1，角色2”，**如果需要在应用中判断用户是否有相应角色，就需要在相应的 Realm 中返回角色信息**，**也就是说 Shiro 不负责维护用户-角色信息，需要应用提供，Shiro 只是提供相应的接口方便验证**，后续会介绍如何动态的获取用户角色。

2、测试用例（com.github.zhangkaitao.shiro.chapter3.RoleTest）

```java
    @Test
    public void testHasRole() {
        login("classpath:shiro-role.ini", "zhang", "123");
        //判断拥有角色：role1
        Assert.assertTrue(subject().hasRole("role1"));
        //判断拥有角色：role1 and role2
        Assert.assertTrue(subject().hasAllRoles(Arrays.asList("role1", "role2")));
        //判断拥有角色：role1 and role2 and !role3
        boolean[] result = subject().hasRoles(Arrays.asList("role1", "role2", "role3"));
        Assert.assertEquals(true, result[0]);
        Assert.assertEquals(true, result[1]);
        Assert.assertEquals(false, result[2]);
    }
```

> subject.hasRole("role2") 返回一个boolean型
> subject.hasAllRoles（List<String> list)返回一个boolean型，判断用户是否拥有所有角色
> **subject.hasRoles（List<String> list)返回一个boolean型数组，通过循环对一个角色进行判断，来进行是否具有其中一个角色**

**Shiro 提供了 hasRole/hasRoles 用于判断用户是否拥有某个角色/某些权限**；但是没有提供如 hashAnyRole 用于判断是否有某些权限中的某一个。

```java
    @Test(expected = UnauthorizedException.class)
    public void testCheckRole() {
        login("classpath:shiro-role.ini", "zhang", "123");
        //断言拥有角色：role1
        subject().checkRole("role1");
        //断言拥有角色：role1 and role3 失败抛出异常
        subject().checkRoles("role1", "role3");
    }
```

**Shiro 提供的 checkRole/checkRoles 和 hasRole/hasAllRoles 不同的地方是它在判断为假的情况下会抛出 UnauthorizedException 异常。**

> 和 assertEquals 和 assertTrue 区别类似，一个可以抛出错误提醒

到此基于角色的访问控制（即隐式角色）就完成了，这种方式的缺点就是如果很多地方进行了角色判断，**但是有一天不需要了那么就需要修改相应代码把所有相关的地方进行删除；这就是粗粒度造成的问题。**

**基于资源的访问控制（显示角色）**

1、在 ini 配置文件配置用户拥有的角色及角色-权限关系（shiro-permission.ini）

```ini
[users]
zhang=123,role1,role2
wang=123,role1
[roles]
role1=user:create,user:update
role2=user:create,user:delete
```

规则：“用户名=密码，角色 1，角色 2” “角色=权限 1，权限 2”，即首先根据用户名找到角色，然后根据角色再找到权限；即角色是权限集合；**Shiro 同样不进行权限的维护，需要我们通过 Realm 返回相应的权限信息。只需要维护“用户——角色”之间的关系即可。**

2、测试用例（com.github.zhangkaitao.shiro.chapter3.PermissionTest）

```java
    @Test
    public void testIsPermitted() {
        login("classpath:shiro-permission.ini", "zhang", "123");
        //判断拥有权限：user:create
        Assert.assertTrue(subject().isPermitted("user:create"));
        //判断拥有权限：user:update and user:delete
        Assert.assertTrue(subject().isPermittedAll("user:update", "user:delete"));
        //判断没有权限：user:view
        Assert.assertFalse(subject().isPermitted("user:view"));
    }
```

**Shiro 提供了 isPermitted 和 isPermittedAll 用于判断用户是否拥有某个权限或所有权限，也没有提供如 isPermittedAny 用于判断拥有某一个权限的接口。**

```java
    @Test(expected = UnauthorizedException.class)
    public void testCheckPermission () {
        login("classpath:shiro-permission.ini", "zhang", "123");
        //断言拥有权限：user:create
        subject().checkPermission("user:create");
        //断言拥有权限：user:delete and user:update
        subject().checkPermissions("user:delete", "user:update");
        //断言拥有权限：user:view 失败抛出异常
        subject().checkPermissions("user:view");
    }
```

但是失败的情况下会抛出 UnauthorizedException 异常。

到此基于资源的访问控制（显示角色）就完成了，也可以叫基于权限的访问控制，这种方式的一般规则是“资源标识符：操作”，即是资源级别的粒度；这种方式的好处就是如果要修改基本都是一个资源级别的修改，不会对其他模块代码产生影响，粒度小。但是实现起来可能稍微复杂点，需要维护“用户——角色，角色——权限（资源：操作）”之间的关系。

## Permission

### 字符串通配符权限

规则：**“资源标识符：操作：对象实例 ID”** 即对哪个资源的哪个实例可以进行什么操作。其默认支持通配符权限字符串，“:”表示**资源/操作/实例的分割**；“,”表示操作的分割；“*”表示任意资源/操作/实例。

1、单个资源单个权限

```java
subject().checkPermissions("system:user:update");
```

用户拥有资源“system:user”的“update”权限。

2、单个资源多个权限

```ini
role41=system:user:update,system:user:delete
```

然后通过如下代码判断

```java
subject().checkPermissions("system:user:update", "system:user:delete");
```

用户拥有资源“system:user”的“update”和“delete”权限。如上可以简写成：

ini 配置（表示角色4拥有 system:user 资源的 update 和 delete 权限）

```ini
role42="system:user:update,delete"
```

接着可以通过如下代码判断

```java
subject().checkPermissions("system:user:update,delete");
```

通过“system:user:update,delete”验证“system:user:update, system:user:delete”是没问题的，但是反过来是规则不成立。

3、单个资源全部权限

ini 配置

```ini
role51="system:user:create,update,delete,view"
```

然后通过如下代码判断

```java
subject().checkPermissions("system:user:create,update,delete,view");
```

用户拥有资源“system:user”的“create”、“update”、“delete”和“view”所有权限。如上可以简写成：

ini 配置文件（表示角色 5 拥有 system:user 的所有权限）

```ini
role52=system:user:*
```

也可以简写为（推荐上边的写法）：

```ini
role53=system:user
```

然后通过如下代码判断

```java
subject().checkPermissions("system:user:*");
subject().checkPermissions("system:user");
```

通过“system:user:*”验证“system:user:create,delete,update:view”可以，但是反过来是不成立的。

4、所有资源单个权限

ini 配置

```ini
role61=*:view
```

然后通过如下代码判断

```ini
subject().checkPermissions("user:view");
```

用户拥有所有资源的“view”所有权限。假设判断的权限是“"system:user:view”，那么需要“role5=::view”这样写才行

5、实例级别的权限

- 单个实例单个权限

ini 配置

```ini
role71=user:view:1
```

对资源 user 的 1 实例拥有 view 权限。

然后通过如下代码判断

```java
subject().checkPermissions("user:view:1");
```

- 单个实例多个权限

ini 配置

```ini
role72="user:update,delete:1"
```

对资源 user 的 1 实例拥有 update、delete 权限。

然后通过如下代码判断

```java
subject().checkPermissions("user:delete,update:1");
subject().checkPermissions("user:update:1", "user:delete:1");
```

- 单个实例所有权限

ini 配置

```ini
role73=user:*:1
```

对资源 user 的 1 实例拥有所有权限。

然后通过如下代码判断

```java
subject().checkPermissions("user:update:1", "user:delete:1", "user:view:1");
```

- 所有实例单个权限

ini 配置

```ini
role74=user:auth:*
```

对资源 user 的 1 实例拥有所有权限。

然后通过如下代码判断

```java
subject().checkPermissions("user:auth:1", "user:auth:2");
```

- 所有实例所有权限

ini 配置

```ini
role75=user:*:*
```

对资源 user 的 1 实例拥有所有权限。

然后通过如下代码判断

```java
subject().checkPermissions("user:view:1", "user:auth:2");
```

6、Shiro 对权限字符串缺失部分的处理

如“user:view”等价于“user:view:*”；而“organization”等价于“organization:*”或者“organization:*:*”。可以这么理解，这种方式实现了前缀匹配。

另外如“user:*”可以匹配如“user:delete”、“user:delete”可以匹配如“user:delete:1”、“user:*:1”可以匹配如“user:view:1”、“user”可以匹配“user:view”或“user:view:1”等。即*可以匹配所有，不加*可以进行前缀匹配；但是如“*:view”不能匹配“system:user:view”，需要使用“*:*:view”，即后缀匹配必须指定前缀（多个冒号就需要多个*来匹配）。

7、WildcardPermission

如下两种方式是等价的：

```java
subject().checkPermission("menu:view:1");
subject().checkPermission(new WildcardPermission("menu:view:1"));
```

因此没什么必要的话使用字符串更方便。

8、性能问题

通配符匹配方式比字符串相等匹配来说是更复杂的，因此需要花费更长时间，但是一般系统的权限不会太多，且可以配合缓存来提供其性能，如果这样性能还达不到要求我们可以实现位操作算法实现性能更好的权限匹配。另外实例级别的权限验证如果数据量太大也不建议使用，可能造成查询权限及匹配变慢。可以考虑比如在sql查询时加上权限字符串之类的方式在查询时就完成了权限匹配。

## 授权流程

![img](https://atts.w3cschool.cn/attachments/day_210114/202101141719562904.png)

流程如下：

1. 首先调用 Subject.isPermitted*/hasRole*接口，其会委托给 SecurityManager，而 SecurityManager 接着会委托给 Authorizer；
2. Authorizer 是真正的授权者，如果我们调用如 isPermitted(“user:view”)，其首先会通过 PermissionResolver 把字符串转换成相应的 Permission 实例；
3. 在进行授权之前，其会调用相应的 Realm 获取 Subject 相应的角色/权限用于匹配传入的角色/权限；
4. Authorizer 会判断 Realm 的角色/权限是否和传入的匹配，如果有多个 Realm，会委托给 ModularRealmAuthorizer 进行循环判断，如果匹配如 isPermitted*/hasRole* 会返回 true，否则返回 false 表示授权失败。

ModularRealmAuthorizer 进行多 Realm 匹配流程：

- 首先检查相应的 Realm 是否实现了实现了 Authorizer；
- 如果实现了 Authorizer，那么接着调用其相应的 isPermitted*/hasRole* 接口进行匹配；
- 如果有一个 Realm 匹配那么将返回 true，否则返回 false。

如果 Realm 进行授权的话，应该继承 AuthorizingRealm，其流程是：

- 如果调用 hasRole*，则直接获取 AuthorizationInfo.getRoles() 与传入的角色比较即可；首先如果调用如 isPermitted(“user:view”)，首先通过 PermissionResolver 将权限字符串转换成相应的 Permission 实例，默认使用 WildcardPermissionResolver，即转换为通配符的 WildcardPermission；
- 通过 AuthorizationInfo.getObjectPermissions() 得到 Permission 实例集合；通过 AuthorizationInfo.getStringPermissions() 得到字符串集合并通过 PermissionResolver 解析为 Permission 实例；然后获取用户的角色，并通过 RolePermissionResolver 解析角色对应的权限集合（默认没有实现，可以自己提供）；
- 接着调用 Permission.implies(Permission p) 逐个与传入的权限比较，如果有匹配的则返回 true，否则 false。

## Authorizer、PermissionResolver及RolePermissionResolver

Authorizer 的职责是进行授权（访问控制），是 Shiro API 中授权核心的入口点，其提供了相应的角色/权限判断接口，具体请参考其 Javadoc。SecurityManager 继承了 Authorizer 接口，且提供了 ModularRealmAuthorizer 用于多 Realm 时的授权匹配。**PermissionResolver 用于解析权限字符串到 Permission 实例，而 RolePermissionResolver 用于根据角色解析相应的权限集合。**

我们可以通过如下 ini 配置更改 Authorizer 实现：

```ini
authorizer=org.apache.shiro.authz.ModularRealmAuthorizer
securityManager.authorizer=$authorizer
```

对于 ModularRealmAuthorizer，相应的 AuthorizingSecurityManager 会在初始化完成后自动将相应的 realm 设置进去，我们也可以通过调用其 setRealms() 方法进行设置。对于实现自己的 authorizer 可以参考 ModularRealmAuthorizer 实现即可，在此就不提供示例了。

设置 ModularRealmAuthorizer 的 permissionResolver，其会自动设置到相应的 Realm 上（其实现了 PermissionResolverAware 接口），如：

```ini
permissionResolver=org.apache.shiro.authz.permission.WildcardPermissionResolver
authorizer.permissionResolver=$permissionResolver
```

设置 ModularRealmAuthorizer 的 rolePermissionResolver，其会自动设置到相应的 Realm 上（其实现了 RolePermissionResolverAware 接口），如：

```ini
rolePermissionResolver=com.github.zhangkaitao.shiro.chapter3.permission.MyRolePermissionResolver
authorizer.rolePermissionResolver=$rolePermissionResolver
```

示例

1、ini 配置（shiro-authorizer.ini）

```ini
[main]
\#自定义authorizer
authorizer=org.apache.shiro.authz.ModularRealmAuthorizer
\#自定义permissionResolver
\#permissionResolver=org.apache.shiro.authz.permission.WildcardPermissionResolver
permissionResolver=com.github.zhangkaitao.shiro.chapter3.permission.BitAndWildPermissionResolver
authorizer.permissionResolver=$permissionResolver
\#自定义rolePermissionResolver
rolePermissionResolver=com.github.zhangkaitao.shiro.chapter3.permission.MyRolePermissionResolver
authorizer.rolePermissionResolver=$rolePermissionResolver
securityManager.authorizer=$authorizer
\#自定义realm 一定要放在securityManager.authorizer赋值之后（因为调用setRealms会将realms设置给authorizer，并给各个Realm设置permissionResolver和rolePermissionResolver）
realm=com.github.zhangkaitao.shiro.chapter3.realm.MyRealm
securityManager.realms=$realm
```

设置 securityManager 的 realms 一定要放到最后，因为在调用 SecurityManager.setRealms 时会将 realms 设置给 authorizer，并为各个 Realm 设置 permissionResolver 和 rolePermissionResolver。另外，不能使用 IniSecurityManagerFactory 创建的 IniRealm，因为其初始化顺序的问题可能造成后续的初始化 Permission 造成影响。

2、定义 BitAndWildPermissionResolver 及 BitPermission

BitPermission 用于实现位移方式的权限，如规则是：

权限字符串格式：+ 资源字符串 + 权限位 + 实例 ID；以 + 开头中间通过 + 分割；权限：0 表示所有权限；1 新增（二进制：0001）、2 修改（二进制：0010）、4 删除（二进制：0100）、8 查看（二进制：1000）；如 +user+10 表示对资源 user 拥有修改 / 查看权限。

```java
public class BitPermission implements Permission {
    private String resourceIdentify;
    private int permissionBit;
    private String instanceId;
    public BitPermission(String permissionString) {
        String[] array = permissionString.split("\\+");
        if(array.length > 1) {
            resourceIdentify = array[1];
        }
        if(StringUtils.isEmpty(resourceIdentify)) {
            resourceIdentify = "*";
        }
        if(array.length > 2) {
            permissionBit = Integer.valueOf(array[2]);
        }
        if(array.length > 3) {
            instanceId = array[3];
        }
        if(StringUtils.isEmpty(instanceId)) {
            instanceId = "*";
        }
    }
    @Override
    public boolean implies(Permission p) {
        if(!(p instanceof BitPermission)) {
            return false;
        }
        BitPermission other = (BitPermission) p;
        if(!("*".equals(this.resourceIdentify) || this.resourceIdentify.equals(other.resourceIdentify))) {
            return false;
        }
        if(!(this.permissionBit ==0 || (this.permissionBit & other.permissionBit) != 0)) {
            return false;
        }
        if(!("*".equals(this.instanceId) || this.instanceId.equals(other.instanceId))) {
            return false;
        }
        return true;
    }
}
```

Permission 接口提供了 boolean implies(Permission p) 方法用于判断权限匹配的；

```java
public class BitAndWildPermissionResolver implements PermissionResolver {
    @Override
    public Permission resolvePermission(String permissionString) {
        if(permissionString.startsWith("+")) {
            return new BitPermission(permissionString);
        }
        return new WildcardPermission(permissionString);
    }
}
```

BitAndWildPermissionResolver 实现了 PermissionResolver 接口，并根据权限字符串是否以 “+” 开头来解析权限字符串为 BitPermission 或 WildcardPermission。

3、定义 MyRolePermissionResolver

RolePermissionResolver 用于根据角色字符串来解析得到权限集合。

```java
public class MyRolePermissionResolver implements RolePermissionResolver {
    @Override
    public Collection<Permission> resolvePermissionsInRole(String roleString) {
        if("role1".equals(roleString)) {
            return Arrays.asList((Permission)new WildcardPermission("menu:*"));
        }
        return null;
    }
}
```

此处的实现很简单，如果用户拥有 role1，那么就返回一个 “menu:*” 的权限。

4、自定义 Realm

```java
public class MyRealm extends AuthorizingRealm {
    @Override
    protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principals) {
        SimpleAuthorizationInfo authorizationInfo = new SimpleAuthorizationInfo();
        authorizationInfo.addRole("role1");
        authorizationInfo.addRole("role2");
        authorizationInfo.addObjectPermission(new BitPermission("+user1+10"));
        authorizationInfo.addObjectPermission(new WildcardPermission("user1:*"));
        authorizationInfo.addStringPermission("+user2+10");
        authorizationInfo.addStringPermission("user2:*");
        return authorizationInfo;
    }
    @Override
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        //和com.github.zhangkaitao.shiro.chapter2.realm.MyRealm1. getAuthenticationInfo代码一样，省略
}
}
```

此时我们继承 AuthorizingRealm 而不是实现 Realm 接口；推荐使用 AuthorizingRealm，因为： AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token)：表示获取身份验证信息；AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principals)：表示根据用户身份获取授权信息。**这种方式的好处是当只需要身份验证时只需要获取身份验证信息而不需要获取授权信息。**对于 AuthenticationInfo 和 AuthorizationInfo 请参考其 Javadoc 获取相关接口信息。

> 在简单整合我们的jwt的时候我们只需要对应获取我们的身份验证信息不需要获取我们的授权信息

另外我们可以使用 JdbcRealm，需要做的操作如下：

1. 执行 sql/ shiro-init-data.sql 插入相关的权限数据；
2. 使用 shiro-jdbc-authorizer.ini 配置文件，需要设置 jdbcRealm.permissionsLookupEnabled 为 true 来开启权限查询。

此次还要注意就是不能把我们自定义的如 “+user1+10” 配置到 INI 配置文件，即使有 IniRealm 完成，因为 IniRealm 在 new 完成后就会解析这些权限字符串，默认使用了WildcardPermissionResolver 完成，即此处是一个设计权限，如果采用生命周期（如使用初始化方法）的方式进行加载就可以解决我们自定义 permissionResolver 的问题。

5、测试用例

```java
public class AuthorizerTest extends BaseTest {
    @Test
    public void testIsPermitted() {
        login("classpath:shiro-authorizer.ini", "zhang", "123");
        //判断拥有权限：user:create
        Assert.assertTrue(subject().isPermitted("user1:update"));
        Assert.assertTrue(subject().isPermitted("user2:update"));
        //通过二进制位的方式表示权限
        Assert.assertTrue(subject().isPermitted("+user1+2"));//新增权限
        Assert.assertTrue(subject().isPermitted("+user1+8"));//查看权限
        Assert.assertTrue(subject().isPermitted("+user2+10"));//新增及查看
        Assert.assertFalse(subject().isPermitted("+user1+4"));//没有删除权限
        Assert.assertTrue(subject().isPermitted("menu:view"));//通过MyRolePermissionResolver解析得到的权限
    }
}
```

通过如上步骤可以实现自定义权限验证了。另外因为不支持 hasAnyRole/isPermittedAny 这种方式的授权，可以参考我的一篇《简单 shiro 扩展实现 NOT、AND、OR 权限验证 》进行简单的扩展完成这个需求，在这篇文章中通过重写 AuthorizingRealm 里的验证逻辑实现的。

# 4、INI 配置（了解）

之前章节我们已经接触过一些 INI 配置规则了，如果大家使用过如 Spring 之类的 IOC/DI 容器的话，Shiro 提供的 INI 配置也是非常类似的，即可以理解为是一个 IOC/DI 容器，但是区别在于它从一个根对象 securityManager 开始。

## 根对象 SecurityManager

从之前的 Shiro 架构图可以看出，Shiro 是从根对象 SecurityManager 进行身份验证和授权的；也就是所有操作都是自它开始的，这个对象是线程安全且真个应用只需要一个即可，因此 Shiro 提供了 SecurityUtils 让我们绑定它为全局的，方便后续操作。

因为 Shiro 的类都是 POJO 的，因此都很容易放到任何 IoC 容器管理。但是和一般的 IoC 容器的区别在于，Shiro 从根对象 securityManager 开始导航；Shiro 支持的依赖注入：public 空参构造器对象的创建、setter 依赖注入。

1、纯 Java 代码写法（com.github.zhangkaitao.shiro.chapter4.NonConfigurationCreateTest）：

```java
DefaultSecurityManager securityManager = new DefaultSecurityManager();
//设置authenticator
ModularRealmAuthenticator authenticator = new ModularRealmAuthenticator();
authenticator.setAuthenticationStrategy(new AtLeastOneSuccessfulStrategy());
securityManager.setAuthenticator(authenticator);
//设置authorizer
ModularRealmAuthorizer authorizer = new ModularRealmAuthorizer();
authorizer.setPermissionResolver(new WildcardPermissionResolver());
securityManager.setAuthorizer(authorizer);
//设置Realm
DruidDataSource ds = new DruidDataSource();
ds.setDriverClassName("com.mysql.jdbc.Driver");
ds.setUrl("jdbc:mysql://localhost:3306/shiro");
ds.setUsername("root");
ds.setPassword("");
JdbcRealm jdbcRealm = new JdbcRealm();
jdbcRealm.setDataSource(ds);
jdbcRealm.setPermissionsLookupEnabled(true);
securityManager.setRealms(Arrays.asList((Realm) jdbcRealm));
//将SecurityManager设置到SecurityUtils 方便全局使用
SecurityUtils.setSecurityManager(securityManager);
Subject subject = SecurityUtils.getSubject();
UsernamePasswordToken token = new UsernamePasswordToken("zhang", "123");
subject.login(token);
Assert.assertTrue(subject.isAuthenticated());
```

2、等价的 INI 配置（shiro-config.ini）

```ini
[main]
\#authenticator
authenticator=org.apache.shiro.authc.pam.ModularRealmAuthenticator
authenticationStrategy=org.apache.shiro.authc.pam.AtLeastOneSuccessfulStrategy
authenticator.authenticationStrategy=$authenticationStrategy
securityManager.authenticator=$authenticator
\#authorizer
authorizer=org.apache.shiro.authz.ModularRealmAuthorizer
permissionResolver=org.apache.shiro.authz.permission.WildcardPermissionResolver
authorizer.permissionResolver=$permissionResolver
securityManager.authorizer=$authorizer
\#realm
dataSource=com.alibaba.druid.pool.DruidDataSource
dataSource.driverClassName=com.mysql.jdbc.Driver
dataSource.url=jdbc:mysql://localhost:3306/shiro
dataSource.username=root
\#dataSource.password=
jdbcRealm=org.apache.shiro.realm.jdbc.JdbcRealm
jdbcRealm.dataSource=$dataSource
jdbcRealm.permissionsLookupEnabled=true
securityManager.realms=$jdbcRealm
```

即使没接触过 IoC 容器的知识，如上配置也是很容易理解的：

1. 对象名 = 全限定类名 相对于调用 public 无参构造器创建对象
2. 对象名. 属性名 = 值 相当于调用 setter 方法设置常量值
3. 对象名. 属性名 =$ 对象引用 相当于调用 setter 方法设置对象引用

3、Java 代码（com.github.zhangkaitao.shiro.chapter4.ConfigurationCreateTest）

```java
Factory<org.apache.shiro.mgt.SecurityManager> factory =
         new IniSecurityManagerFactory("classpath:shiro-config.ini");
org.apache.shiro.mgt.SecurityManager securityManager = factory.getInstance();
//将SecurityManager设置到SecurityUtils 方便全局使用
SecurityUtils.setSecurityManager(securityManager);
Subject subject = SecurityUtils.getSubject();
UsernamePasswordToken token = new UsernamePasswordToken("zhang", "123");
subject.login(token);
Assert.assertTrue(subject.isAuthenticated());
```

如上代码是从 Shiro INI 配置中获取相应的 securityManager 实例：

1. 默认情况先创建一个名字为 securityManager，类型为 org.apache.shiro.mgt.DefaultSecurityManager 的默认的 SecurityManager，如果想自定义，只需要在 ini 配置文件中指定 “securityManager=SecurityManager 实现类” 即可，名字必须为 securityManager，它是起始的根；
2. IniSecurityManagerFactory 是创建 securityManager 的工厂，其需要一个 ini 配置文件路径，其支持 “classpath:”（类路径）、“file:”（文件系统）、“url:”（网络）三种路径格式，默认是文件系统；
3. 接着获取 SecuriyManager 实例，后续步骤和之前的一样。

从如上可以看出 Shiro INI 配置方式本身提供了一个简单的 IoC/DI 机制方便在配置文件配置，但是是从 securityManager 这个根对象开始导航。

## INI 配置

**ini 配置文件类似于 Java 中的 properties（key=value）**，不过提供了将 key/value 分类的特性，key 是每个部分不重复即可，而不是整个配置文件。如下是 INI 配置分类：

```ini
[main]
\#提供了对根对象securityManager及其依赖的配置
securityManager=org.apache.shiro.mgt.DefaultSecurityManager
…………
securityManager.realms=$jdbcRealm
[users]
\#提供了对用户/密码及其角色的配置，用户名=密码，角色1，角色2
username=password,role1,role2
[roles]
\#提供了角色及权限之间关系的配置，角色=权限1，权限2
role1=permission1,permission2
[urls]
\#用于web，提供了对web url拦截相关的配置，url=拦截器[参数]，拦截器
/index.html = anon
/admin/** = authc, roles[admin], perms["permission1"]
```

**[main] 部分**

提供了对根对象 securityManager 及其依赖对象的配置。

**创建对象**

```ini
securityManager=org.apache.shiro.mgt.DefaultSecurityManager
```

其构造器必须是 public 空参构造器，通过反射创建相应的实例。

**常量值 setter 注入**

```ini
dataSource.driverClassName=com.mysql.jdbc.Driver
jdbcRealm.permissionsLookupEnabled=true
```

会自动调用 jdbcRealm.setPermissionsLookupEnabled(true)，对于这种常量值会自动类型转换。

**对象引用 setter 注入**

```ini
authenticator=org.apache.shiro.authc.pam.ModularRealmAuthenticator
authenticationStrategy=org.apache.shiro.authc.pam.AtLeastOneSuccessfulStrategy
authenticator.authenticationStrategy=$authenticationStrategy
securityManager.authenticator=$authenticator
```

会自动通过 securityManager.setAuthenticator(authenticator) 注入引用依赖。

**嵌套属性 setter 注入**

```ini
securityManager.authenticator.authenticationStrategy=$authenticationStrategy
```

也支持这种嵌套方式的 setter 注入。

**byte 数组 setter 注入**

```ini
\#base64 byte[]
authenticator.bytes=aGVsbG8=
\#hex byte[]
authenticator.bytes=0x68656c6c6f&nbsp;
```

默认需要使用 Base64 进行编码，也可以使用 0x 十六进制。

**Array/Set/List setter 注入**

```ini
authenticator.array=1,2,3
authenticator.set=$jdbcRealm,$jdbcRealm
```

多个之间通过 “，” 分割。

**Map setter 注入**

```ini
authenticator.map=$jdbcRealm:$jdbcRealm,1:1,key:abc
```

即格式是：map=key：value，key：value，可以注入常量及引用值，常量的话都看作字符串（即使有泛型也不会自动造型）。

**实例化 / 注入顺序**

```ini
realm=Realm1
realm=Realm12
authenticator.bytes=aGVsbG8=
authenticator.bytes=0x68656c6c6f&nbsp; 
```

后边的覆盖前边的注入。

测试用例请参考配置文件 shiro-config-main.ini。

**[users] 部分**

配置用户名 / 密码及其角色，格式：“用户名 = 密码，角色 1，角色 2”，角色部分可省略。如：

```ini
[users]
zhang=123,role1,role2
wang=123
```

密码一般生成其摘要 / 加密存储，后续章节介绍。

**[roles] 部分**

配置角色及权限之间的关系，格式：“角色 = 权限 1，权限 2”；如：

```ini
[roles]
role1=user:create,user:update
role2=*
```

如果只有角色没有对应的权限，可以不配 roles，具体规则请参考授权章节。

**[urls] 部分**

配置 url 及相应的拦截器之间的关系，格式：“url = 拦截器 [参数]，拦截器 [参数]，如：

```ini
[urls]
/admin/** = authc, roles[admin], perms["permission1"]
```

具体规则参见 web 相关章节。

# 5、Shiro 编码加密

## 编码/加密

在涉及到密码存储问题上，应该加密 / 生成密码摘要存储，而不是存储明文密码。比如之前的 600w csdn 账号泄露对用户可能造成很大损失，因此应加密 / 生成不可逆的摘要方式存储。

**什么是MD5？**

MD5一般用来加密或者签名。
特点：MD5算法是不可逆的，内容相同的无论执行多少次MD5生产的结果都一致，都会生产一个16进制的32位长度字符串

我们一般在业务层(Service层)使用我们的MD5/SHA 来对我们的密码+salt进行加密处理。

**什么是盐？**

盐是我们生产的一个随机数列（我们推荐每一个用户对应的盐是不一致的，保存在数据库中的User表中）来进行对密码的加密算法。

如果有坏蛋入侵我们的数据库，再不解也要猜测我们的盐逻辑，即我们的盐在密码的第几位。甚至我们可以定义我们的私盐和公盐，即私盐是我们用户自己的盐，而公盐是我们公司内部高级机密，两个盐进行复合再利用MD5进行加密

> 此时，我们的客户在前端在前端界面输入正确的密码会经过以下的步骤：
> 1、调用我们的服务层Service根据用户的Id进行用户的Salt的调取
> 2、对用户输入的密码和盐（单盐/私盐和多盐）进行MD5加密，对比两者是否相同
> 3、查询数据库对应的加密过后的密码和现在输入的密码的加密后是否相同，相同则登录成功，否则登入失败

## 编码 / 解码

Shiro 提供了 base64 和 16 进制字符串编码 / 解码的 API 支持，方便一些编码解码操作。Shiro 内部的一些数据的存储 / 表示都使用了 base64 和 16 进制字符串。

base64 编码/解码操作：

```java
String str = "hello";
String base64Encoded = Base64.encodeToString(str.getBytes());
String str2 = Base64.decodeToString(base64Encoded);
```

16进制字符串编码/解码操作：

```java
String str = "hello";
String base64Encoded = Hex.encodeToString(str.getBytes());
String str2 = new String(Hex.decode(base64Encoded.getBytes()));
```

通过如上方式可以进行 16 进制字符串编码 / base64 编码解码操作，更多 API 请参考其 Javadoc。

>1、Base64.encodeToString(Byte[] byte): 以 *encoding* 指定的Base64编码格式生产编码。
>2、Base64.decodeToString(String str): 以 *encoding* 指定的Base64编码格式解码字符串。默认编码为字符串编码。
>3、Hex.encodeToString(Byte[] byte): 以 *encoding* 指定的16进制编码格式生产编码。
>4、Hex.decode(Byte[] byte)： 以 *encoding* 指定的16进制编码格式解析编码。
>**注意：我们的Base64和16进制解码的参数是不一样的**

还有一个可能经常用到的类 CodecSupport，提供了 toBytes(str,"utf-8") / toString(bytes,"utf-8") 用于在 byte 数组 /String 之间转换。

## 散列算法

散列算法一般用于生成数据的摘要信息，是一种不可逆的算法，一般适合存储密码之类的数据，常见的散列算法如 MD5、SHA 等。一般进行散列时最好提供一个 salt（盐），比如加密密码 “admin”，产生的散列值是 “21232f297a57a5a743894a0e4a801fc3”，可以到一些 md5 解密网站很容易的通过散列值得到密码 “admin”，即如果直接对密码进行散列相对来说破解更容易，此时我们可以加一些只有系统知道的干扰数据，如用户名和 ID（即盐）；这样散列的对象是 “密码 + 用户名 +ID”，这样生成的散列值相对来说更难破解。

**下面是md5算法：**

```java
String str = "hello";
String salt = "123";
String md5 = new Md5Hash(str, salt).toString();//还可以转换为 toBase64()/toHex()
```

如上代码通过盐 “123”MD5 散列 “hello”。另外散列时还可以指定散列次数。对应的原码为

```java
public Md5Hash(Object source, Object salt, int hashIterations) {
    super("MD5", source, salt, hashIterations);
  }
```

**下面是sha256算法**

```java
String str = "hello";
String salt = "123";
String sha1 = new Sha256Hash(str, salt).toString();
```

使用 SHA256 算法生成相应的散列数据，另外还有如 SHA1、SHA512 算法。

**Shiro 还提供了通用的散列支持：**

```java
String str = "hello";
String salt = "123";
//内部使用MessageDigest
String simpleHash = new SimpleHash("SHA-1", str, salt).toString();  
```

通过调用 SimpleHash 时指定散列算法，其内部使用了 Java 的 MessageDigest 实现。

为了方便使用，Shiro 提供了 HashService，默认提供了 DefaultHashService 实现。

```java
DefaultHashService hashService = new DefaultHashService(); //默认算法SHA-512
hashService.setHashAlgorithmName("SHA-512");
hashService.setPrivateSalt(new SimpleByteSource("123")); //私盐，默认无
hashService.setGeneratePublicSalt(true);//是否生成公盐，默认false
hashService.setRandomNumberGenerator(new SecureRandomNumberGenerator());//用于生成公盐。默认就这个
hashService.setHashIterations(1); //生成Hash值的迭代次数
HashRequest request = new HashRequest.Builder()
            .setAlgorithmName("MD5").setSource(ByteSource.Util.bytes("hello"))
            .setSalt(ByteSource.Util.bytes("123")).setIterations(2).build();
String hex = hashService.computeHash(request).toHex();
```

1. 首先创建一个 DefaultHashService，默认使用 SHA-512 算法；
2. 以通过 hashAlgorithmName 属性修改算法；
3. 可以通过 privateSalt 设置一个私盐，其在散列时自动与用户传入的公盐混合产生一个新盐；
4. 可以通过 generatePublicSalt 属性在用户没有传入公盐的情况下是否生成公盐；
5. 可以设置 randomNumberGenerator 用于生成公盐；
6. 可以设置 hashIterations 属性来修改默认加密迭代次数；
7. 需要构建一个 HashRequest，传入算法、数据、公盐、迭代次数。

SecureRandomNumberGenerator 用于生成一个随机数：

```java
SecureRandomNumberGenerator randomNumberGenerator =
     new SecureRandomNumberGenerator();
randomNumberGenerator.setSeed("123".getBytes());
String hex = randomNumberGenerator.nextBytes().toHex();
```

## 使用md5或者sha256

我们一般要构建一个对应的小Shrio工具类来封装我们的加密方法

**情况一、**

**在数据库的密码已经进行加密，而且是md5+salt+迭代加密，用户在输入密码的验证**

编写shiro工具类如下：

```java
public shrioUtils(){
public HashedCredentialsMatcher HashUtil(String str,int i){
    HashedCredentialsMatcher matcher = new HashedCredentialsMatcher();
	matcher.setHashAlgorithmName(str); //加密方式
	matcher.setHashIterations(i);   //迭代次数
    return march;
}
public  HashedCredentialsMatcher HashUtil(String str){
	HashUtil(str,1);}
}
```

此时对应的有

```java
@Autowired
ShrioUtils shrioUtils
    
TestRealm realm = new TestRealm()
realm.setCredentialsMatcher(shrioUtils.HashUtil("md5",1024))
```

## 加密 / 解密

Shiro 还提供对称式加密 / 解密算法的支持，如 AES、Blowfish 等；当前还没有提供对非对称加密 / 解密算法支持，未来版本可能提供。

AES 算法实现：

```java
AesCipherService aesCipherService = new AesCipherService();
aesCipherService.setKeySize(128); //设置key长度
//生成key
Key key = aesCipherService.generateNewKey();
String text = "hello";
//加密
String encrptText = 
aesCipherService.encrypt(text.getBytes(), key.getEncoded()).toHex();
//解密
String text2 =
 new String(aesCipherService.decrypt(Hex.decode(encrptText), key.getEncoded()).getBytes());
Assert.assertEquals(text, text2);
```

更多算法请参考示例 com.github.zhangkaitao.shiro.chapter5.hash.CodecAndCryptoTest。

## PasswordService/CredentialsMatcher

Shiro 提供了 PasswordService 及 CredentialsMatcher 用于提供加密密码及验证密码服务。

```java
public interface PasswordService {
    //输入明文密码得到密文密码
    String encryptPassword(Object plaintextPassword) throws IllegalArgumentException;
}
public interface CredentialsMatcher {
    //匹配用户输入的token的凭证（未加密）与系统提供的凭证（已加密）
    boolean doCredentialsMatch(AuthenticationToken token, AuthenticationInfo info);
}
```

Shiro 默认提供了 PasswordService 实现 DefaultPasswordService；**CredentialsMatcher 的实现有 PasswordMatcher 和HashedCredentialsMatcher（更强大）。**

**DefaultPasswordService 配合 PasswordMatcher 实现简单的密码加密与验证服务**

1、定义 Realm（com.github.zhangkaitao.shiro.chapter5.hash.realm.MyRealm）

```java
public class MyRealm extends AuthorizingRealm {
    private PasswordService passwordService;
    public void setPasswordService(PasswordService passwordService) {
        this.passwordService = passwordService;
    }
     //省略doGetAuthorizationInfo，具体看代码 
    @Override
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        return new SimpleAuthenticationInfo(
                "wu",                passwordService.encryptPassword("123"),
                getName());
    }
}
```

为了方便，直接注入一个 passwordService 来加密密码，实际使用时需要在 Service 层使用 passwordService 加密密码并存到数据库。

2、ini 配置（shiro-passwordservice.ini）

```ini
[main]
passwordService=org.apache.shiro.authc.credential.DefaultPasswordService
hashService=org.apache.shiro.crypto.hash.DefaultHashService
passwordService.hashService=$hashService
hashFormat=org.apache.shiro.crypto.hash.format.Shiro1CryptFormat
passwordService.hashFormat=$hashFormat
hashFormatFactory=org.apache.shiro.crypto.hash.format.DefaultHashFormatFactory
passwordService.hashFormatFactory=$hashFormatFactory
passwordMatcher=org.apache.shiro.authc.credential.PasswordMatcher
passwordMatcher.passwordService=$passwordService
myRealm=com.github.zhangkaitao.shiro.chapter5.hash.realm.MyRealm
myRealm.passwordService=$passwordService
myRealm.credentialsMatcher=$passwordMatcher
securityManager.realms=$myRealm
```

- passwordService 使用 DefaultPasswordService，如果有必要也可以自定义；
- hashService 定义散列密码使用的 HashService，默认使用 DefaultHashService（默认 SHA-256 算法）；
- hashFormat 用于对散列出的值进行格式化，默认使用 Shiro1CryptFormat，另外提供了 Base64Format 和 HexFormat，对于有 salt 的密码请自定义实现 ParsableHashFormat 然后把 salt 格式化到散列值中；
- hashFormatFactory 用于根据散列值得到散列的密码和 salt；因为如果使用如 SHA 算法，那么会生成一个 salt，此 salt 需要保存到散列后的值中以便之后与传入的密码比较时使用；默认使用 DefaultHashFormatFactory；
- passwordMatcher 使用 PasswordMatcher，其是一个 CredentialsMatcher 实现；
- 将 credentialsMatcher 赋值给 myRealm，myRealm 间接继承了 AuthenticatingRealm，其在调用 getAuthenticationInfo 方法获取到 AuthenticationInfo 信息后，会使用 credentialsMatcher 来验证凭据是否匹配，如果不匹配将抛出 IncorrectCredentialsException 异常。

3、测试用例请参考 com.github.zhangkaitao.shiro.chapter5.hash.PasswordTest。

另外可以参考配置 shiro-jdbc-passwordservice.ini，提供了 JdbcRealm 的测试用例，测试前请先调用 sql/shiro-init-data.sql 初始化用户数据。

如上方式的缺点是：salt 保存在散列值中；没有实现如密码重试次数限制。

**HashedCredentialsMatcher 实现密码验证服务**

Shiro 提供了 CredentialsMatcher 的散列实现 HashedCredentialsMatcher，和之前的 PasswordMatcher 不同的是，它只用于密码验证，且可以提供自己的盐，而不是随机生成盐，且生成密码散列值的算法需要自己写，因为能提供自己的盐。

1、生成密码散列值

此处我们使用 MD5 算法，“密码 + 盐（用户名 + 随机数）” 的方式生成散列值：

```java
String algorithmName = "md5";
String username = "liu";
String password = "123";
String salt1 = username;
String salt2 = new SecureRandomNumberGenerator().nextBytes().toHex();
int hashIterations = 2;
SimpleHash hash = new SimpleHash(algorithmName, password, salt1 + salt2, hashIterations);
String encodedPassword = hash.toHex();
```

如果要写用户模块，需要在新增用户 / 重置密码时使用如上算法保存密码，将生成的密码及 salt2 存入数据库（因为我们的散列算法是：md5(md5(密码 +username+salt2))）。

2、生成 Realm（com.github.zhangkaitao.shiro.chapter5.hash.realm.MyRealm2）

```java
protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
    String username = "liu"; //用户名及salt1
    String password = "202cb962ac59075b964b07152d234b70"; //加密后的密码
    String salt2 = "202cb962ac59075b964b07152d234b70";
SimpleAuthenticationInfo ai = 
        new SimpleAuthenticationInfo(username, password, getName());
    ai.setCredentialsSalt(ByteSource.Util.bytes(username+salt2)); //盐是用户名+随机数
        return ai;
}
```

此处就是把步骤 1 中生成的相应数据组装为 SimpleAuthenticationInfo，通过 SimpleAuthenticationInfo 的 credentialsSalt 设置盐，HashedCredentialsMatcher 会自动识别这个盐。

如果使用 JdbcRealm，需要修改获取用户信息（包括盐）的 `sql：“select password, password_salt from users where username = ?”`，而我们的盐是由 username+password_salt 组成，所以需要通过如下 ini 配置（shiro-jdbc-hashedCredentialsMatcher.ini）修改：

```ini
jdbcRealm.saltStyle=COLUMN
jdbcRealm.authenticationQuery=select password, concat(username,password_salt) from users where username = ?
jdbcRealm.credentialsMatcher=$credentialsMatcher
```

- saltStyle 表示使用密码 + 盐的机制，authenticationQuery 第一列是密码，第二列是盐；
- 通过 authenticationQuery 指定密码及盐查询 SQL；

此处还要注意 Shiro 默认使用了 apache commons BeanUtils，默认是不进行 Enum 类型转型的，此时需要自己注册一个 Enum 转换器 “BeanUtilsBean.getInstance().getConvertUtils().register(new EnumConverter(), JdbcRealm.SaltStyle.class);” 具体请参考示例 “com.github.zhangkaitao.shiro.chapter5.hash.PasswordTest” 中的代码。

另外可以参考配置 shiro-jdbc-passwordservice.ini，提供了 JdbcRealm 的测试用例，测试前请先调用 sql/shiro-init-data.sql 初始化用户数据。

3、ini 配置（shiro-hashedCredentialsMatcher.ini）

```ini
[main]
credentialsMatcher=org.apache.shiro.authc.credential.HashedCredentialsMatcher
credentialsMatcher.hashAlgorithmName=md5
credentialsMatcher.hashIterations=2
credentialsMatcher.storedCredentialsHexEncoded=true
myRealm=com.github.zhangkaitao.shiro.chapter5.hash.realm.MyRealm2
myRealm.credentialsMatcher=$credentialsMatcher
securityManager.realms=$myRealm
```

- 通过 credentialsMatcher.hashAlgorithmName=md5 指定散列算法为 md5，需要和生成密码时的一样；
- credentialsMatcher.hashIterations=2，散列迭代次数，需要和生成密码时的意义；
- credentialsMatcher.storedCredentialsHexEncoded=true 表示是否存储散列后的密码为 16 进制，需要和生成密码时的一样，默认是 base64；

此处最需要注意的就是 HashedCredentialsMatcher 的算法需要和生成密码时的算法一样。另外 HashedCredentialsMatcher 会自动根据 AuthenticationInfo 的类型是否是 SaltedAuthenticationInfo 来获取 credentialsSalt 盐。

4、测试用例请参考 com.github.zhangkaitao.shiro.chapter5.hash.PasswordTest。

**密码重试次数限制**

如在 1 个小时内密码最多重试 5 次，如果尝试次数超过 5 次就锁定 1 小时，1 小时后可再次重试，如果还是重试失败，可以锁定如 1 天，以此类推，防止密码被暴力破解。我们通过继承 HashedCredentialsMatcher，且使用 Ehcache 记录重试次数和超时时间。

com.github.zhangkaitao.shiro.chapter5.hash.credentials.RetryLimitHashedCredentialsMatcher：

```java
public boolean doCredentialsMatch(AuthenticationToken token, AuthenticationInfo info) {
       String username = (String)token.getPrincipal();
        //retry count + 1
        Element element = passwordRetryCache.get(username);
        if(element == null) {
            element = new Element(username , new AtomicInteger(0));
            passwordRetryCache.put(element);
        }
        AtomicInteger retryCount = (AtomicInteger)element.getObjectValue();
        if(retryCount.incrementAndGet() > 5) {
            //if retry count > 5 throw
            throw new ExcessiveAttemptsException();
        }
        boolean matches = super.doCredentialsMatch(token, info);
        if(matches) {
            //clear retry count
            passwordRetryCache.remove(username);
        }
        return matches;
}
```

如上代码逻辑比较简单，即如果密码输入正确清除 cache 中的记录；否则 cache 中的重试次数 +1，如果超出 5 次那么抛出异常表示超出重试次数了。

# 6、Shiro Realm

## Realm 及相关对象

## Realm

【Realm】及【Authorizer】部分都已经详细介绍过 Realm 了，接下来再来看一下一般真实环境下的 Realm 如何实现。

**1、定义实体及关系**

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/7.png)

即用户 - 角色之间是多对多关系，角色 - 权限之间是多对多关系；且用户和权限之间通过角色建立关系；在系统中验证时通过权限验证，角色只是权限集合，即所谓的显示角色；其实权限应该对应到资源（如菜单、URL、页面按钮、Java 方法等）中，即应该将权限字符串存储到资源实体中，但是目前为了简单化，直接提取一个权限表，【综合示例】部分会使用完整的表结构。

**用户实体包括：**

- 编号 (id)
- 用户名 (username)
- 密码 (password)
- 盐 (salt)
- 是否锁定 (locked)；是否锁定用于封禁用户使用，其实最好使用 Enum 字段存储，可以实现更复杂的用户状态实现。 

**角色实体包括：**

- 编号 (id)
- 角色标识符（role）
- 描述（description）
- 是否可用（available）；其中角色标识符用于在程序中进行隐式角色判断的，描述用于以后再前台界面显示的、是否可用表示角色当前是否激活。 

**权限实体包括：**

- 编号（id）
- 权限标识符（permission）
- 描述（description）
- 是否可用（available）；含义和角色实体类似不再阐述。

**另外还有两个关系实体：用户 - 角色实体（用户编号、角色编号，且组合为复合主键）；角色 - 权限实体（角色编号、权限编号，且组合为复合主键）。**

sql 及实体请参考源代码中的 sql\shiro.sql 和 com.github.zhangkaitao.shiro.chapter6.entity 对应的实体。

Shiro 中 Realm 的继承结构如下：

![img](https://atts.w3cschool.cn/attachments/image/20200728/1595899224993079.png)

**2、环境准备**

为了方便数据库操作，使用了 “org.springframework: spring-jdbc: 4.0.0.RELEASE” 依赖，虽然是 spring4 版本的，但使用上和 spring3 无区别。其他依赖请参考源码的 pom.xml。

**3、定义 Service 及 Dao**

为了实现的简单性，只实现必须的功能，其他的可以自己实现即可。

**PermissionService**

```java
public interface PermissionService {
    public Permission createPermission(Permission permission);
    public void deletePermission(Long permissionId);
}
```

实现基本的创建 / 删除权限。

**RoleService**

```java
public interface RoleService {
    public Role createRole(Role role);
    public void deleteRole(Long roleId);
    //添加角色-权限之间关系
    public void correlationPermissions(Long roleId, Long... permissionIds);
    //移除角色-权限之间关系
    public void uncorrelationPermissions(Long roleId, Long... permissionIds);//
}
```

相对于 PermissionService 多了关联 / 移除关联角色 - 权限功能。

**UserService**

```java
public interface UserService {
    public User createUser(User user); //创建账户
    public void changePassword(Long userId, String newPassword);//修改密码
    public void correlationRoles(Long userId, Long... roleIds); //添加用户-角色关系
    public void uncorrelationRoles(Long userId, Long... roleIds);// 移除用户-角色关系
    public User findByUsername(String username);// 根据用户名查找用户
    public Set<String> findRoles(String username);// 根据用户名查找其角色
    public Set<String> findPermissions(String username); //根据用户名查找其权限
}
```

此处使用 findByUsername、findRoles 及 findPermissions 来查找用户名对应的帐号、角色及权限信息。之后的 Realm 就使用这些方法来查找相关信息。

**UserServiceImpl**

```java
public User createUser(User user) {
    //加密密码
    passwordHelper.encryptPassword(user);
    return userDao.createUser(user);
}
public void changePassword(Long userId, String newPassword) {
    User user = userDao.findOne(userId);
    user.setPassword(newPassword);
    passwordHelper.encryptPassword(user);
    userDao.updateUser(user);
}
```

在创建账户及修改密码时直接把生成密码操作委托给 PasswordHelper。

**PasswordHelper**

```java
public class PasswordHelper {
    private RandomNumberGenerator randomNumberGenerator =
     new SecureRandomNumberGenerator();
    private String algorithmName = "md5";
    private final int hashIterations = 2;
    public void encryptPassword(User user) {
        user.setSalt(randomNumberGenerator.nextBytes().toHex());
        String newPassword = new SimpleHash(
                algorithmName,
                user.getPassword(),
                ByteSource.Util.bytes(user.getCredentialsSalt()),
                hashIterations).toHex();
        user.setPassword(newPassword);
    }
}
```

之后的 CredentialsMatcher 需要和此处加密的算法一样。user.getCredentialsSalt() 辅助方法返回 username+salt。

为了节省篇幅，对于 DAO/Service 的接口及实现，具体请参考源码com.github.zhangkaitao.shiro.chapter6。另外请参考 Service 层的测试用例 com.github.zhangkaitao.shiro.chapter6.service.ServiceTest。

**4、定义 Realm**

**RetryLimitHashedCredentialsMatcher**
和第五章的一样，在此就不罗列代码了，请参考源码 com.github.zhangkaitao.shiro.chapter6.credentials.RetryLimitHashedCredentialsMatcher。

**UserRealm**

另外请参考 Service 层的测试用例 com.github.zhangkaitao.shiro.chapter6.service.ServiceTest。

```java
public class UserRealm extends AuthorizingRealm {
    private UserService userService = new UserServiceImpl();
    protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principals) {
        String username = (String)principals.getPrimaryPrincipal();
        SimpleAuthorizationInfo authorizationInfo = new SimpleAuthorizationInfo();
        authorizationInfo.setRoles(userService.findRoles(username));
        authorizationInfo.setStringPermissions(userService.findPermissions(username));
        return authorizationInfo;
    }
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        String username = (String)token.getPrincipal();
        User user = userService.findByUsername(username);
        if(user == null) {
            throw new UnknownAccountException();//没找到帐号
        }
        if(Boolean.TRUE.equals(user.getLocked())) {
            throw new LockedAccountException(); //帐号锁定
        }
        //交给AuthenticatingRealm使用CredentialsMatcher进行密码匹配，如果觉得人家的不好可以在此判断或自定义实现
        SimpleAuthenticationInfo authenticationInfo = new SimpleAuthenticationInfo(
                user.getUsername(), //用户名
                user.getPassword(), //密码
                ByteSource.Util.bytes(user.getCredentialsSalt()),//salt=username+salt
                getName()  //realm name
        );
        return authenticationInfo;
    }
}
```

**1、UserRealm 父类 AuthorizingRealm 将获取 Subject 相关信息分成两步**：获取身份验证信息（doGetAuthenticationInfo）及授权信息（doGetAuthorizationInfo）；

**2、doGetAuthenticationInfo 获取身份验证相关信息**：首先根据传入的用户名获取 User 信息；然后如果 user 为空，那么抛出没找到帐号异常 UnknownAccountException；如果 user 找到但锁定了抛出锁定异常 LockedAccountException；最后生成 AuthenticationInfo 信息，交给间接父类 AuthenticatingRealm 使用 CredentialsMatcher 进行判断密码是否匹配，如果不匹配将抛出密码错误异常 IncorrectCredentialsException；另外如果密码重试此处太多将抛出超出重试次数异常 ExcessiveAttemptsException；在组装 SimpleAuthenticationInfo 信息时，需要传入：身份信息（用户名）、凭据（密文密码）、盐（username+salt），CredentialsMatcher 使用盐加密传入的明文密码和此处的密文密码进行匹配。

**3、doGetAuthorizationInfo 获取授权信息**：PrincipalCollection 是一个身份集合，因为我们现在就一个 Realm，所以直接调用 getPrimaryPrincipal 得到之前传入的用户名即可；然后根据用户名调用 UserService 接口获取角色及权限信息。

**5、测试用例**

为了节省篇幅，请参考测试用例 com.github.zhangkaitao.shiro.chapter6.realm.UserRealmTest。包含了：登录成功、用户名错误、密码错误、密码超出重试次数、有 / 没有角色、有 / 没有权限的测试。

## AuthenticationToken

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/8.png)

AuthenticationToken 用于收集用户提交的身份（如用户名）及凭据（如密码）：

```java
public interface AuthenticationToken extends Serializable {
    Object getPrincipal(); //身份
    Object getCredentials(); //凭据
}
```

扩展接口 RememberMeAuthenticationToken：提供了 “boolean isRememberMe()” 现“记住我”的功能； 扩展接口是 HostAuthenticationToken：提供了 “String getHost()” 方法用于获取用户 “主机” 的功能。

Shiro 提供了一个直接拿来用的 UsernamePasswordToken，用于实现用户名 / 密码 Token 组，另外其实现了 RememberMeAuthenticationToken 和 HostAuthenticationToken，可以实现记住我及主机验证的支持。

## AuthenticationInfo

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/9.png)

AuthenticationInfo 有两个作用：

1. 如果 Realm 是 AuthenticatingRealm 子类，则提供给 AuthenticatingRealm 内部使用的 CredentialsMatcher 进行凭据验证；（如果没有继承它需要在自己的 Realm 中自己实现验证）；
2. 提供给 SecurityManager 来创建 Subject（提供身份信息）；

MergableAuthenticationInfo 用于提供在多 Realm 时合并 AuthenticationInfo 的功能，主要合并 Principal、如果是其他的如 credentialsSalt，会用后边的信息覆盖前边的。

比如 HashedCredentialsMatcher，在验证时会判断 AuthenticationInfo 是否是 SaltedAuthenticationInfo 子类，来获取盐信息。

Account 相当于我们之前的 User，SimpleAccount 是其一个实现；在 IniRealm、PropertiesRealm 这种静态创建帐号信息的场景中使用，这些 Realm 直接继承了 SimpleAccountRealm，而 SimpleAccountRealm 提供了相关的 API 来动态维护 SimpleAccount；即可以通过这些 API 来动态增删改查 SimpleAccount；动态增删改查角色 / 权限信息。及如果您的帐号不是特别多，可以使用这种方式，具体请参考 SimpleAccountRealm Javadoc。

其他情况一般返回 SimpleAuthenticationInfo 即可。

## PrincipalCollection

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/10.png)

因为我们可以在 Shiro 中同时配置多个 Realm，所以呢身份信息可能就有多个；因此其提供了 PrincipalCollection 用于聚合这些身份信息：

```java
public interface PrincipalCollection extends Iterable, Serializable {
    Object getPrimaryPrincipal(); //得到主要的身份
    <T> T oneByType(Class<T> type); //根据身份类型获取第一个
    <T> Collection<T> byType(Class<T> type); //根据身份类型获取一组
    List asList(); //转换为List
    Set asSet(); //转换为Set
    Collection fromRealm(String realmName); //根据Realm名字获取
    Set<String> getRealmNames(); //获取所有身份验证通过的Realm名字
    boolean isEmpty(); //判断是否为空
}
```

因为 PrincipalCollection 聚合了多个，此处最需要注意的是 getPrimaryPrincipal，如果只有一个 Principal 那么直接返回即可，如果有多个 Principal，则返回第一个（因为内部使用 Map 存储，所以可以认为是返回任意一个）；oneByType / byType 根据凭据的类型返回相应的 Principal；fromRealm 根据 Realm 名字（每个 Principal 都与一个 Realm 关联）获取相应的 Principal。

MutablePrincipalCollection 是一个可变的 PrincipalCollection 接口，即提供了如下可变方法：

```java
public interface MutablePrincipalCollection extends PrincipalCollection {
    void add(Object principal, String realmName); //添加Realm-Principal的关联
    void addAll(Collection principals, String realmName); //添加一组Realm-Principal的关联
    void addAll(PrincipalCollection principals);//添加PrincipalCollection
    void clear();//清空
}
```

目前 Shiro 只提供了一个实现 SimplePrincipalCollection，还记得之前的 AuthenticationStrategy 实现嘛，用于在多 Realm 时判断是否满足条件的，在大多数实现中（继承了 AbstractAuthenticationStrategy）afterAttempt 方法会进行 AuthenticationInfo（实现了 MergableAuthenticationInfo）的 merge，比如 SimpleAuthenticationInfo 会合并多个 Principal 为一个 PrincipalCollection。

对于 PrincipalMap 是 Shiro 1.2 中的一个实验品，暂时无用，具体可以参考其 Javadoc。接下来通过示例来看看 PrincipalCollection。

**1、准备三个 Realm**

**MyRealm1**

```java
public class MyRealm1 implements Realm {
    @Override
    public String getName() {
        return "a"; //realm name 为 “a”
    }
    //省略supports方法，具体请见源码
    @Override
    public AuthenticationInfo getAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        return new SimpleAuthenticationInfo(
                "zhang", //身份 字符串类型
                "123",   //凭据
                getName() //Realm Name
        );
    }
}
```

**MyRealm2**

和 MyRealm1 完全一样，只是 Realm 名字为 b。

**MyRealm3**

```java
public class MyRealm3 implements Realm {
    @Override
    public String getName() {
        return "c"; //realm name 为 “c”
    }
    //省略supports方法，具体请见源码
    @Override
    public AuthenticationInfo getAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        User user = new User("zhang", "123");
        return new SimpleAuthenticationInfo(
                user, //身份 User类型
                "123",   //凭据
                getName() //Realm Name
        );
    }
}
```

和 MyRealm1 同名，但返回的 Principal 是 User 类型。

**2、ini 配置（shiro-multirealm.ini）**

```ini
[main]
realm1=com.github.zhangkaitao.shiro.chapter6.realm.MyRealm1
realm2=com.github.zhangkaitao.shiro.chapter6.realm.MyRealm2
realm3=com.github.zhangkaitao.shiro.chapter6.realm.MyRealm3
securityManager.realms=$realm1,$realm2,$realm3
```

**3、测试用例（com.github.zhangkaitao.shiro.chapter6.realm.PrincialCollectionTest）**

因为我们的 Realm 中没有进行身份及凭据验证，所以相当于身份验证都是成功的，都将返回：

```java
Object primaryPrincipal1 = subject.getPrincipal();
PrincipalCollection princialCollection = subject.getPrincipals();
Object primaryPrincipal2 = princialCollection.getPrimaryPrincipal();
```

我们可以直接调用 subject.getPrincipal 获取 PrimaryPrincipal（即所谓的第一个）；或者通过 getPrincipals 获取 PrincipalCollection；然后通过其 getPrimaryPrincipal 获取 PrimaryPrincipal。

```java
Set<String> realmNames = princialCollection.getRealmNames();
```

获取所有身份验证成功的 Realm 名字。

```java
Set<Object> principals = princialCollection.asSet(); //asList 和 asSet 的结果一样
```

将身份信息转换为 Set/List，即使转换为 List，也是先转换为 Set 再完成的。

```java
Collection<User> users = princialCollection.fromRealm("c");
```

根据 Realm 名字获取身份，因为 Realm 名字可以重复，所以可能多个身份，建议 Realm 名字尽量不要重复。

## AuthorizationInfo

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/11.png)

AuthorizationInfo 用于聚合授权信息的：

```java
public interface AuthorizationInfo extends Serializable {
    Collection<String> getRoles(); //获取角色字符串信息
    Collection<String> getStringPermissions(); //获取权限字符串信息
    Collection<Permission> getObjectPermissions(); //获取Permission对象信息
}
```

当我们使用 AuthorizingRealm 时，如果身份验证成功，在进行授权时就通过 doGetAuthorizationInfo 方法获取角色 / 权限信息用于授权验证。

Shiro 提供了一个实现 SimpleAuthorizationInfo，大多数时候使用这个即可。

对于 Account 及 SimpleAccount，之前的【6.3 AuthenticationInfo】已经介绍过了，用于 SimpleAccountRealm 子类，实现动态角色 / 权限维护的。

## Subject

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/12.png)

Subject 是 Shiro 的核心对象，基本所有身份验证、授权都是通过 Subject 完成。

**1、身份信息获取**

```java
Object getPrincipal(); //Primary Principal
PrincipalCollection getPrincipals(); // PrincipalCollection
```

**2、身份验证**

```java
void login(AuthenticationToken token) throws AuthenticationException;
boolean isAuthenticated();
boolean isRemembered();
```

通过 login 登录，如果登录失败将抛出相应的 AuthenticationException，如果登录成功调用 isAuthenticated 就会返回 true，即已经通过身份验证；如果 isRemembered 返回 true，表示是通过记住我功能登录的而不是调用 login 方法登录的。isAuthenticated/isRemembered 是互斥的，即如果其中一个返回 true，另一个返回 false。

**3、角色授权验证**

```java
boolean hasRole(String roleIdentifier);
boolean[] hasRoles(List<String> roleIdentifiers);
boolean hasAllRoles(Collection<String> roleIdentifiers);
void checkRole(String roleIdentifier) throws AuthorizationException;
void checkRoles(Collection<String> roleIdentifiers) throws AuthorizationException;
void checkRoles(String... roleIdentifiers) throws AuthorizationException;
```

hasRole *进行角色验证，验证后返回 true/false；而 checkRole* 验证失败时抛出 AuthorizationException 异常。

**4、权限授权验证**

```java
boolean isPermitted(String permission);
boolean isPermitted(Permission permission);
boolean[] isPermitted(String... permissions);
boolean[] isPermitted(List<Permission> permissions);
boolean isPermittedAll(String... permissions);
boolean isPermittedAll(Collection<Permission> permissions);
void checkPermission(String permission) throws AuthorizationException;
void checkPermission(Permission permission) throws AuthorizationException;
void checkPermissions(String... permissions) throws AuthorizationException;
void checkPermissions(Collection<Permission> permissions) throws AuthorizationException;
```

isPermitted *进行权限验证，验证后返回 true/false；而 checkPermission* 验证失败时抛出 AuthorizationException。

**5、会话**

```java
Session getSession(); //相当于getSession(true)
Session getSession(boolean create); 
```

类似于 Web 中的会话。如果登录成功就相当于建立了会话，接着可以使用 getSession 获取；如果 create=false 如果没有会话将返回 null，而 create=true 如果没有会话会强制创建一个。

**6、退出**

```java
void logout();
```

**7、RunAs**

```java
void runAs(PrincipalCollection principals) throws NullPointerException, IllegalStateException;
boolean isRunAs();
PrincipalCollection getPreviousPrincipals();
PrincipalCollection releaseRunAs();
```

RunAs 即实现 “允许 A 假设为 B 身份进行访问”；通过调用 subject.runAs(b) 进行访问；接着调用 subject.getPrincipals 将获取到 B 的身份；此时调用 isRunAs 将返回 true；而 a 的身份需要通过 subject. getPreviousPrincipals 获取；如果不需要 RunAs 了调用 subject. releaseRunAs 即可。

**8、多线程**

```java
<V> V execute(Callable<V> callable) throws ExecutionException;
void execute(Runnable runnable);
<V> Callable<V> associateWith(Callable<V> callable);
Runnable associateWith(Runnable runnable);
```

实现线程之间的 Subject 传播，因为 Subject 是线程绑定的；因此在多线程执行中需要传播到相应的线程才能获取到相应的 Subject。最简单的办法就是通过 execute(runnable/callable 实例) 直接调用；或者通过 associateWith(runnable/callable 实例) 得到一个包装后的实例；它们都是通过：1、把当前线程的 Subject 绑定过去；2、在线程执行结束后自动释放。

Subject 自己不会实现相应的身份验证 / 授权逻辑，而是通过 DelegatingSubject 委托给 SecurityManager 实现；及可以理解为 Subject 是一个面门。

对于 Subject 的构建一般没必要我们去创建；一般通过 SecurityUtils.getSubject() 获取：

```java
public static Subject getSubject() {
    Subject subject = ThreadContext.getSubject();
    if (subject == null) {
        subject = (new Subject.Builder()).buildSubject();
        ThreadContext.bind(subject);
    }
    return subject;
}
```

即首先查看当前线程是否绑定了 Subject，如果没有通过 Subject.Builder 构建一个然后绑定到现场返回。

如果想自定义创建，可以通过：

```java
new Subject.Builder().principals(身份).authenticated(true/false).buildSubject()
```

这种可以创建相应的 Subject 实例了，然后自己绑定到线程即可。在 new Builder() 时如果没有传入 SecurityManager，自动调用 SecurityUtils.getSecurityManager 获取；也可以自己传入一个实例。

对于 Subject 我们一般这么使用：

1. 身份验证（login）
2. 授权（hasRole*/isPermitted* 或 checkRole*/checkPermission*）
3. 将相应的数据存储到会话（Session）
4. 切换身份（RunAs）/ 多线程身份传播
5. 退出

而我们必须的功能就是 1、2、5。到目前为止我们就可以使用 Shiro 进行应用程序的安全控制了，但是还是缺少如对 Web 验证、Java 方法验证等的一些简化实现。

# 7、Shiro Web 集成

## 与 Web 集成

Shiro 提供了与 Web 集成的支持，其通过一个 ShiroFilter 入口来拦截需要安全控制的 URL，然后进行相应的控制，ShiroFilter 类似于如 Strut2/SpringMVC 这种 web 框架的前端控制器，其是安全控制的入口点，其负责读取配置（如 ini 配置文件），然后判断 URL 是否需要登录 / 权限等工作。

## 准备环境

**1、创建 webapp 应用**

此处我们使用了 jetty-maven-plugin 和 tomcat7-maven-plugin 插件；这样可以直接使用 “mvn jetty:run” 或“mvn tomcat7:run”直接运行 webapp 了。然后通过 URLhttp://localhost:8080/chapter7 / 访问即可。

**2、依赖**

Servlet3

```xml
<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>3.0.1</version>
    <scope>provided</scope>
</dependency>
```

Servlet3 的知识可以参考 https://github.com/zhangkaitao/servlet3-showcase 及 Servlet3 规范 http://www.iteye.com/blogs/subjects/Servlet-3-1。

shiro-web

```xml
<dependency>
    <groupId>org.apache.shiro</groupId>
    <artifactId>shiro-web</artifactId>
    <version>1.2.2</version>
</dependency>
```

其他依赖请参考源码的 pom.xml。

## ShiroFilter 入口

**1、Shiro 1.1 及以前版本配置方式**

```xml
<filter>
    <filter-name>iniShiroFilter</filter-name>
    <filter-class>org.apache.shiro.web.servlet.IniShiroFilter</filter-class>
    <init-param>
        <param-name>configPath</param-name>
        <param-value>classpath:shiro.ini</param-value>
    </init-param>
</filter>
<filter-mapping>
    <filter-name>iniShiroFilter</filter-name>
    <url-pattern>/*</url-pattern>
</filter-mapping>
```

1. 使用 IniShiroFilter 作为 Shiro 安全控制的入口点，通过 url-pattern 指定需要安全的 URL；
2. 通过 configPath 指定 ini 配置文件位置，默认是先从 /WEB-INF/shiro.ini 加载，如果没有就默认加载 classpath:shiro.ini，即默认相对于 web 应用上下文根路径；
3. 也可以通过如下方式直接内嵌 ini 配置文件内容到 web.xml。

```xml
<init-param>
    <param-name>config</param-name>
    <param-value>
        ini配置文件贴在这
    </param-value>
</init-param>
```

**2、Shiro 1.2 及以后版本的配置方式**

从 Shiro 1.2 开始引入了 Environment/WebEnvironment 的概念，即由它们的实现提供相应的 SecurityManager 及其相应的依赖。ShiroFilter 会自动找到 Environment 然后获取相应的依赖。

```xml
<listener>
   <listener-class>org.apache.shiro.web.env.EnvironmentLoaderListener</listener-class>
</listener>
```

通过 EnvironmentLoaderListener 来创建相应的 WebEnvironment，并自动绑定到 ServletContext，默认使用 IniWebEnvironment 实现。

可以通过如下配置修改默认实现及其加载的配置文件位置：

```xml
<context-param>
   <param-name>shiroEnvironmentClass</param-name>
   <param-value>org.apache.shiro.web.env.IniWebEnvironment</param-value>
</context-param>
    <context-param>
        <param-name>shiroConfigLocations</param-name>
        <param-value>classpath:shiro.ini</param-value>
    </context-param>
```

shiroConfigLocations 默认是 “/WEB-INF/shiro.ini”，IniWebEnvironment 默认是先从 / WEB-INF/shiro.ini 加载，如果没有就默认加载 classpath:shiro.ini。

**3、与 Spring 集成**

```xml
<filter>
    <filter-name>shiroFilter</filter-name>
    <filter-class>org.springframework.web.filter.DelegatingFilterProxy</filter-class>
    <init-param>
        <param-name>targetFilterLifecycle</param-name>
        <param-value>true</param-value>
    </init-param>
</filter>
<filter-mapping>
    <filter-name>shiroFilter</filter-name>
    <url-pattern>/*</url-pattern>
</filter-mapping>
```

DelegatingFilterProxy 作用是自动到 spring 容器查找名字为 shiroFilter（filter-name）的 bean 并把所有 Filter 的操作委托给它。然后将 ShiroFilter 配置到 spring 容器即可：

```xml
<bean id="shiroFilter" class="org.apache.shiro.spring.web.ShiroFilterFactoryBean">
<property name="securityManager" ref="securityManager"/>
<!—忽略其他，详见与Spring集成部分 -->
</bean>
```

最后不要忘了使用 org.springframework.web.context.ContextLoaderListener 加载这个 spring 配置文件即可。因为我们现在的 shiro 版本是 1.2 的，因此之后的测试都是使用 1.2 的配置。

## Web INI 配置

ini 配置部分和之前的相比将多出对 url 部分的配置。

```ini
[main]
\#默认是/login.jsp
authc.loginUrl=/login
roles.unauthorizedUrl=/unauthorized
perms.unauthorizedUrl=/unauthorized
[users]
zhang=123,admin
wang=123
[roles]
admin=user:*,menu:*
[urls]
/login=anon
/unauthorized=anon
/static/**=anon
/authenticated=authc
/role=authc,roles[admin]
/permission=authc,perms["user:create"]
```

其中最重要的就是 [urls] 部分的配置，其格式是： “url = 拦截器 [参数]，拦截器[参数]”；即如果当前请求的 url 匹配[urls] 部分的某个 url 模式，将会执行其配置的拦截器。比如 anon 拦截器表示匿名访问（即不需要登录即可访问）；authc 拦截器表示需要身份认证通过后才能访问；roles[admin]拦截器表示需要有 admin 角色授权才能访问；而 perms["user:create"]拦截器表示需要有 “user:create” 权限才能访问。

**url 模式使用 Ant 风格模式**
Ant 路径通配符支持?、、**，注意通配符匹配不包括目录分隔符 “/”：
**?：匹配一个字符**，如”/admin?” 将匹配 / admin1、admin2，但不匹配 / admin 或 / admin123；
***：匹配零个或多个字符串**，如 / admin \* 将匹配 / admin、/admin123，但不匹配 / admin/1；
\**：匹配路径中的零个或多个路径**，如 / admin/** 将匹配 / admin/a 或 / admin/a/b。

**url 模式匹配顺序**

url 模式匹配顺序是按照在配置中的声明顺序匹配，即从头开始使用第一个匹配的 url 模式对应的拦截器链。如：

```ini
/bb/**=filter1
/bb/aa=filter2
/**=filter3
```

如果请求的 url 是 “/bb/aa”，因为按照声明顺序进行匹配，那么将使用 filter1 进行拦截。

拦截器将在下一节详细介绍。接着我们来看看身份验证、授权及退出在 web 中如何实现。

### 身份验证（登录）

**首先配置需要身份验证的 url**

```ini
/authenticated=authc
/role=authc,roles[admin]
/permission=authc,perms["user:create"]
```

即访问这些地址时会首先判断用户有没有登录，如果没有登录默会跳转到登录页面，默认是 / login.jsp，可以通过在 [main] 部分通过如下配置修改：

```ini
authc.loginUrl=/login
```

**登录 Servlet（com.github.zhangkaitao.shiro.chapter7.web.servlet.LoginServlet）**

```java
@WebServlet(name = "loginServlet", urlPatterns = "/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
        req.getRequestDispatcher("/WEB-INF/jsp/login.jsp").forward(req, resp);
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
        String error = null;
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        Subject subject = SecurityUtils.getSubject();
        UsernamePasswordToken token = new UsernamePasswordToken(username, password);
        try {
            subject.login(token);
        } catch (UnknownAccountException e) {
            error = "用户名/密码错误";
        } catch (IncorrectCredentialsException e) {
            error = "用户名/密码错误";
        } catch (AuthenticationException e) {
            //其他错误，比如锁定，如果想单独处理请单独catch处理
            error = "其他错误：" + e.getMessage();
        }
        if(error != null) {//出错了，返回登录页面
            req.setAttribute("error", error);
            req.getRequestDispatcher("/WEB-INF/jsp/login.jsp").forward(req, resp);
        } else {//登录成功
            req.getRequestDispatcher("/WEB-INF/jsp/loginSuccess.jsp").forward(req, resp);
        }
    }
}
```

1. doGet 请求时展示登录页面；
2. doPost 时进行登录，登录时收集 username/password 参数，然后提交给 Subject 进行登录。如果有错误再返回到登录页面；否则跳转到登录成功页面（此处应该返回到访问登录页面之前的那个页面，或者没有上一个页面时访问主页）。
3. JSP 页面请参考源码。

**测试**

首先输入 http://localhost:8080/chapter7/login 进行登录，登录成功后接着可以访问 http://localhost:8080/chapter7/authenticated 来显示当前登录的用户：

```
${subject.principal} 身份验证已通过。
```

当前实现的一个缺点就是，永远返回到同一个成功页面（比如首页），在实际项目中比如支付时如果没有登录将跳转到登录页面，登录成功后再跳回到支付页面；对于这种功能大家可以在登录时把当前请求保存下来，然后登录成功后再重定向到该请求即可。

Shiro 内置了登录（身份验证）的实现：基于表单的和基于 Basic 的验证，其通过拦截器实现。

### 基于 Basic 的拦截器身份验证

**shiro-basicfilterlogin.ini 配置**

```ini
[main]
authcBasic.applicationName=please login
………省略users
[urls]
/role=authcBasic,roles[admin]
```

1、authcBasic 是 org.apache.shiro.web.filter.authc.BasicHttpAuthenticationFilter 类型的实例，其用于实现基于 Basic 的身份验证；applicationName 用于弹出的登录框显示信息使用，如图：

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/13.png)

2、[urls] 部分配置了 /role 地址需要走 authcBasic 拦截器，即如果访问 /role 时还没有通过身份验证那么将弹出如上图的对话框进行登录，登录成功即可访问。

**web.xml**

把 shiroConfigLocations 改为 shiro-basicfilterlogin.ini 即可。

**测试**

输入 [http://localhost:8080/chapter7/role](http://localhost:8080/chapter7/role，会弹出之前的)，会弹出之前的 Basic 验证对话框输入 “zhang/123” 即可登录成功进行访问。

### 基于表单的拦截器身份验证

基于表单的拦截器身份验证和【1】类似，但是更简单，因为其已经实现了大部分登录逻辑；我们只需要指定：登录地址 / 登录失败后错误信息存哪 / 成功的地址即可。

**shiro-formfilterlogin.ini**

```ini
[main]
authc.loginUrl=/formfilterlogin
authc.usernameParam=username
authc.passwordParam=password
authc.successUrl=/
authc.failureKeyAttribute=shiroLoginFailure
[urls]
/role=authc,roles[admin]
```

1、authc 是 org.apache.shiro.web.filter.authc.FormAuthenticationFilter 类型的实例，其用于实现基于表单的身份验证；通过 loginUrl 指定当身份验证时的登录表单；usernameParam 指定登录表单提交的用户名参数名；passwordParam 指定登录表单提交的密码参数名；successUrl 指定登录成功后重定向的默认地址（默认是 “/”）（如果有上一个地址会自动重定向带该地址）；failureKeyAttribute 指定登录失败时的 request 属性 key（默认 shiroLoginFailure）；这样可以在登录表单得到该错误 key 显示相应的错误消息；

**web.xml**

把 shiroConfigLocations 改为 shiro-formfilterlogin.ini 即可。

**登录 Servlet**

```java
@WebServlet(name = "formFilterLoginServlet", urlPatterns = "/formfilterlogin")
public class FormFilterLoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
        doPost(req, resp);
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
     throws ServletException, IOException {
        String errorClassName = (String)req.getAttribute("shiroLoginFailure");
        if(UnknownAccountException.class.getName().equals(errorClassName)) {
            req.setAttribute("error", "用户名/密码错误");
        } else if(IncorrectCredentialsException.class.getName().equals(errorClassName)) {
            req.setAttribute("error", "用户名/密码错误");
        } else if(errorClassName != null) {
            req.setAttribute("error", "未知错误：" + errorClassName);
        }
        req.getRequestDispatcher("/WEB-INF/jsp/formfilterlogin.jsp").forward(req, resp);
    }
}
```

在登录 Servlet 中通过 shiroLoginFailure 得到 authc 登录失败时的异常类型名，然后根据此异常名来决定显示什么错误消息。

**测试**

输入 `http://localhost:8080/chapter7/role`，会跳转到 “/formfilterlogin” 登录表单，提交表单如果 authc 拦截器登录成功后，会直接重定向会之前的地址 “/role”；假设我们直接访问 “/formfilterlogin” 的话登录成功将直接到默认的 successUrl。

### 授权（角色 / 权限验证）

**shiro.ini**

```ini
[main]
roles.unauthorizedUrl=/unauthorized
perms.unauthorizedUrl=/unauthorized
 [urls]
/role=authc,roles[admin]
/permission=authc,perms["user:create"]
```

通过 unauthorizedUrl 属性指定如果授权失败时重定向到的地址。roles 是 org.apache.shiro.web.filter.authz.RolesAuthorizationFilter 类型的实例，通过参数指定访问时需要的角色，如 “[admin]”，如果有多个使用 “，” 分割，且验证时是 hasAllRole 验证，即且的关系。Perms 是 org.apache.shiro.web.filter.authz.PermissionsAuthorizationFilter 类型的实例，和 roles 类似，只是验证权限字符串。

**web.xml**

把 shiroConfigLocations 改为 shiro.ini 即可。

**RoleServlet/PermissionServlet**

```java
@WebServlet(name = "permissionServlet", urlPatterns = "/permission")
public class PermissionServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
        Subject subject = SecurityUtils.getSubject();
        subject.checkPermission("user:create");
        req.getRequestDispatcher("/WEB-INF/jsp/hasPermission.jsp").forward(req, resp);
    }
}
@WebServlet(name = "roleServlet", urlPatterns = "/role")
public class RoleServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
        Subject subject = SecurityUtils.getSubject();
        subject.checkRole("admin");
        req.getRequestDispatcher("/WEB-INF/jsp/hasRole.jsp").forward(req, resp);
    }
}
```

**测试**

首先访问 `http://localhost:8080/chapter7/login`，使用帐号 “zhang/123” 进行登录，再访问 /role 或 /permission 时会跳转到成功页面（因为其授权成功了）；如果使用帐号 “wang/123” 登录成功后访问这两个地址会跳转到 “/unauthorized” 即没有授权页面。

### 退出

**shiro.ini**

```ini
[urls]
/logout=anon
```

指定 /logout 使用 anon 拦截器即可，即不需要登录即可访问。

**LogoutServlet**

```java
@WebServlet(name = "logoutServlet", urlPatterns = "/logout")
public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
        SecurityUtils.getSubject().logout();
        req.getRequestDispatcher("/WEB-INF/jsp/logoutSuccess.jsp").forward(req, resp);
    }
}
```

直接调用 Subject.logout 即可，退出成功后转发 / 重定向到相应页面即可。

**测试**

首先访问 `http://localhost:8080/chapter7/login`，使用帐号 “zhang/123” 进行登录，登录成功后访问 /logout 即可退出。

Shiro 也提供了 logout 拦截器用于退出，其是 org.apache.shiro.web.filter.authc.LogoutFilter 类型的实例，我们可以在 shiro.ini 配置文件中通过如下配置完成退出：

```ini
[main]
logout.redirectUrl=/login
[urls]
/logout2=logout
```

通过 logout.redirectUrl 指定退出后重定向的地址；通过 /logout2=logout 指定退出 url 是 /logout2。这样当我们登录成功后然后访问 /logout2 即可退出。

# 8、Shiro 会话管理

> 在前后端分离的项目中，我们要禁用我们的Session会话

## 会话管理

Shiro 提供了完整的企业级会话管理功能，不依赖于底层容器（如 web 容器 tomcat），不管 JavaSE 还是 JavaEE 环境都可以使用，提供了会话管理、会话事件监听、会话存储 / 持久化、容器无关的集群、失效 / 过期支持、对 Web 的透明支持、SSO 单点登录的支持等特性。即直接使用 Shiro 的会话管理可以直接替换如 Web 容器的会话管理。

## 会话

所谓会话，即用户访问应用时保持的连接关系，在多次交互中应用能够识别出当前访问的用户是谁，且可以在多次交互中保存一些数据。如访问一些网站时登录成功后，网站可以记住用户，且在退出之前都可以识别当前用户是谁。

Shiro 的会话支持不仅可以在普通的 JavaSE 应用中使用，也可以在 JavaEE 应用中使用，如 web 应用。且使用方式是一致的。

```java
login("classpath:shiro.ini", "zhang", "123");
Subject subject = SecurityUtils.getSubject();
Session session = subject.getSession();
```

登录成功后使用 Subject.getSession() 即可获取会话；其等价于 Subject.getSession(true)，即如果当前没有创建 Session 对象会创建一个；另外 Subject.getSession(false)，如果当前没有创建 Session 则返回 null（不过默认情况下如果启用会话存储功能的话在创建 Subject 时会主动创建一个 Session）。

```java
session.getId();
```

获取当前会话的唯一标识。

```java
session.getHost();
```

获取当前 Subject 的主机地址，该地址是通过 HostAuthenticationToken.getHost() 提供的。

```java
session.getTimeout();
session.setTimeout(毫秒);
```

获取 / 设置当前 Session 的过期时间；如果不设置默认是会话管理器的全局过期时间。

```java
session.getStartTimestamp();
session.getLastAccessTime();
```

获取会话的启动时间及最后访问时间；如果是 JavaSE 应用需要自己定期调用 session.touch() 去更新最后访问时间；如果是 Web 应用，每次进入 ShiroFilter 都会自动调用 session.touch() 来更新最后访问时间。

```java
session.touch();
session.stop();
```

更新会话最后访问时间及销毁会话；当 Subject.logout() 时会自动调用 stop 方法来销毁会话。如果在 web 中，调用 javax.servlet.http.HttpSession. invalidate() 也会自动调用 Shiro Session.stop 方法进行销毁 Shiro 的会话。

```java
session.setAttribute("key", "123");
Assert.assertEquals("123", session.getAttribute("key"));
session.removeAttribute("key");
```

设置 / 获取 / 删除会话属性；在整个会话范围内都可以对这些属性进行操作。

Shiro 提供的会话可以用于 JavaSE/JavaEE 环境，不依赖于任何底层容器，可以独立使用，是完整的会话模块。

## 会话管理器

会话管理器管理着应用中所有 Subject 的会话的创建、维护、删除、失效、验证等工作。是 Shiro 的核心组件，顶层组件 SecurityManager 直接继承了 SessionManager，且提供了SessionsSecurityManager 实现直接把会话管理委托给相应的 SessionManager，DefaultSecurityManager 及 DefaultWebSecurityManager 默认 SecurityManager 都继承了 SessionsSecurityManager。

SecurityManager 提供了如下接口：

```java
Session start(SessionContext context); //启动会话
Session getSession(SessionKey key) throws SessionException; //根据会话Key获取会话
```

另外用于 Web 环境的 WebSessionManager 又提供了如下接口：

```java
boolean isServletContainerSessions();// 是否使用 Servlet 容器的会话
```

Shiro 还提供了 ValidatingSessionManager 用于验资并过期会话：

```java
void validateSessions();// 验证所有会话是否过期
```

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/15.png)

Shiro 提供了三个默认实现：

**DefaultSessionManager**：DefaultSecurityManager 使用的默认实现，用于 JavaSE 环境；
**ServletContainerSessionManager**：DefaultWebSecurityManager 使用的默认实现，用于 Web 环境，其直接使用 Servlet 容器的会话；
**DefaultWebSessionManager**：用于 Web 环境的实现，可以替代 ServletContainerSessionManager，自己维护着会话，直接废弃了 Servlet 容器的会话管理。

替换 SecurityManager 默认的 SessionManager 可以在 ini 中配置（shiro.ini）：

```ini
[main]
sessionManager=org.apache.shiro.session.mgt.DefaultSessionManager
securityManager.sessionManager=$sessionManager
```

Web 环境下的 ini 配置 (shiro-web.ini)：

```ini
<!--EndFragment-->
[main]
sessionManager=org.apache.shiro.web.session.mgt.ServletContainerSessionManager
securityManager.sessionManager=$sessionManager
```

另外可以设置会话的全局过期时间（毫秒为单位），默认 30 分钟：

```ini
sessionManager. globalSessionTimeout=1800000
```

默认情况下 globalSessionTimeout 将应用给所有 Session。可以单独设置每个 Session 的 timeout 属性来为每个 Session 设置其超时时间。

另外如果使用 ServletContainerSessionManager 进行会话管理，Session 的超时依赖于底层 Servlet 容器的超时时间，可以在 web.xml 中配置其会话的超时时间（分钟为单位）：

```xml
<session-config>
  <session-timeout>30</session-timeout>
</session-config>
```

在 Servlet 容器中，默认使用 JSESSIONID Cookie 维护会话，且会话默认是跟容器绑定的；在某些情况下可能需要使用自己的会话机制，此时我们可以使用 DefaultWebSessionManager 来维护会话：

```ini
sessionIdCookie=org.apache.shiro.web.servlet.SimpleCookie
sessionManager=org.apache.shiro.web.session.mgt.DefaultWebSessionManager
sessionIdCookie.name=sid
\#sessionIdCookie.domain=sishuok.com
\#sessionIdCookie.path=
sessionIdCookie.maxAge=1800
sessionIdCookie.httpOnly=true
sessionManager.sessionIdCookie=$sessionIdCookie
sessionManager.sessionIdCookieEnabled=true
securityManager.sessionManager=$sessionManager
```

- sessionIdCookie 是 sessionManager 创建会话 Cookie 的模板：
- sessionIdCookie.name：设置 Cookie 名字，默认为 JSESSIONID；
- sessionIdCookie.domain：设置 Cookie 的域名，默认空，即当前访问的域名；
- sessionIdCookie.path：设置 Cookie 的路径，默认空，即存储在域名根下；
- sessionIdCookie.maxAge：设置 Cookie 的过期时间，秒为单位，默认 - 1 表示关闭浏览器时过期 Cookie；
- sessionIdCookie.httpOnly：如果设置为 true，则客户端不会暴露给客户端脚本代码，使用 HttpOnly cookie 有助于减少某些类型的跨站点脚本攻击；此特性需要实现了 Servlet 2.5 MR6 及以上版本的规范的 Servlet 容器支持；
- sessionManager.sessionIdCookieEnabled：是否启用 / 禁用 Session Id Cookie，默认是启用的；如果禁用后将不会设置 Session Id Cookie，即默认使用了 Servlet 容器的 JSESSIONID，且通过 URL 重写（URL 中的 “;JSESSIONID=id” 部分）保存 Session Id。

另外我们可以如 “sessionManager. sessionIdCookie.name=sid” 这种方式操作 Cookie 模板。

## 会话监听器

会话监听器用于监听会话创建、过期及停止事件：

```java
public class MySessionListener1 implements SessionListener {
    @Override
    public void onStart(Session session) {//会话创建时触发
        System.out.println("会话创建：" + session.getId());
    }
    @Override
    public void onExpiration(Session session) {//会话过期时触发
        System.out.println("会话过期：" + session.getId());
    }
    @Override
    public void onStop(Session session) {//退出/会话过期时触发
        System.out.println("会话停止：" + session.getId());
    }  
}
```

如果只想监听某一个事件，可以继承 SessionListenerAdapter 实现：

```java
public class MySessionListener2 extends SessionListenerAdapter {
    @Override
    public void onStart(Session session) {
        System.out.println("会话创建：" + session.getId());
    }
}
```

在 shiro-web.ini 配置文件中可以进行如下配置设置会话监听器：

```ini
sessionListener1=com.github.zhangkaitao.shiro.chapter10.web.listener.MySessionListener1
sessionListener2=com.github.zhangkaitao.shiro.chapter10.web.listener.MySessionListener2
sessionManager.sessionListeners=$sessionListener1,$sessionListener2
```

## 会话存储 / 持久化

Shiro 提供 SessionDAO 用于会话的 CRUD，即 DAO（Data Access Object）模式实现：

```java
//如DefaultSessionManager在创建完session后会调用该方法；如保存到关系数据库/文件系统/NoSQL数据库；即可以实现会话的持久化；返回会话ID；主要此处返回的ID.equals(session.getId())；
Serializable create(Session session);
//根据会话ID获取会话
Session readSession(Serializable sessionId) throws UnknownSessionException;
//更新会话；如更新会话最后访问时间/停止会话/设置超时时间/设置移除属性等会调用
void update(Session session) throws UnknownSessionException;
//删除会话；当会话过期/会话停止（如用户退出时）会调用
void delete(Session session);
//获取当前所有活跃用户，如果用户量多此方法影响性能
Collection<Session> getActiveSessions();
```

Shiro 内嵌了如下 SessionDAO 实现：

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/16.png)

AbstractSessionDAO 提供了 SessionDAO 的基础实现，如生成会话 ID 等；CachingSessionDAO 提供了对开发者透明的会话缓存的功能，只需要设置相应的 CacheManager 即可；MemorySessionDAO 直接在内存中进行会话维护；而 EnterpriseCacheSessionDAO 提供了缓存功能的会话维护，默认情况下使用 MapCache 实现，内部使用 ConcurrentHashMap 保存缓存的会话。

可以通过如下配置设置 SessionDAO：

```ini
sessionDAO=org.apache.shiro.session.mgt.eis.EnterpriseCacheSessionDAO
sessionManager.sessionDAO=$sessionDAO
```

Shiro 提供了使用 Ehcache 进行会话存储，Ehcache 可以配合 TerraCotta 实现容器无关的分布式集群。

首先在 pom.xml 里添加如下依赖：

```xml
<dependency>
    <groupId>org.apache.shiro</groupId>
    <artifactId>shiro-ehcache</artifactId>
    <version>1.2.2</version>
</dependency>
```

接着配置 shiro-web.ini 文件：

```ini
sessionDAO=org.apache.shiro.session.mgt.eis.EnterpriseCacheSessionDAO
sessionDAO. activeSessionsCacheName=shiro-activeSessionCache
sessionManager.sessionDAO=$sessionDAO
cacheManager = org.apache.shiro.cache.ehcache.EhCacheManager
cacheManager.cacheManagerConfigFile=classpath:ehcache.xml
securityManager.cacheManager = $cacheManager
```

- sessionDAO. activeSessionsCacheName：设置 Session 缓存名字，默认就是 shiro-activeSessionCache；
- cacheManager：缓存管理器，用于管理缓存的，此处使用 Ehcache 实现；
- cacheManager.cacheManagerConfigFile：设置 ehcache 缓存的配置文件；
- securityManager.cacheManager：设置 SecurityManager 的 cacheManager，会自动设置实现了 CacheManagerAware 接口的相应对象，如 SessionDAO 的 cacheManager；

然后配置 ehcache.xml：

```xml
<cache name="shiro-activeSessionCache"
       maxEntriesLocalHeap="10000"
       overflowToDisk="false"
       eternal="false"
       diskPersistent="false"
       timeToLiveSeconds="0"
       timeToIdleSeconds="0"
       statistics="true"/>
```

Cache 的名字为 shiro-activeSessionCache，即设置的 sessionDAO 的 activeSessionsCacheName 属性值。

另外可以通过如下 ini 配置设置会话 ID 生成器：

```ini
sessionIdGenerator=org.apache.shiro.session.mgt.eis.JavaUuidSessionIdGenerator
sessionDAO.sessionIdGenerator=$sessionIdGenerator
```

用于生成会话 ID，默认就是 JavaUuidSessionIdGenerator，使用 java.util.UUID 生成。

如果自定义实现 SessionDAO，继承 CachingSessionDAO 即可：

```java
public class MySessionDAO extends CachingSessionDAO {
    private JdbcTemplate jdbcTemplate = JdbcTemplateUtils.jdbcTemplate();
     protected Serializable doCreate(Session session) {
        Serializable sessionId = generateSessionId(session);
        assignSessionId(session, sessionId);
        String sql = "insert into sessions(id, session) values(?,?)";
        jdbcTemplate.update(sql, sessionId, SerializableUtils.serialize(session));
        return session.getId();
    }
protected void doUpdate(Session session) {
    if(session instanceof ValidatingSession && !((ValidatingSession)session).isValid()) {
        return; //如果会话过期/停止 没必要再更新了
    }
        String sql = "update sessions set session=? where id=?";
        jdbcTemplate.update(sql, SerializableUtils.serialize(session), session.getId());
    }
    protected void doDelete(Session session) {
        String sql = "delete from sessions where id=?";
        jdbcTemplate.update(sql, session.getId());
    }
    protected Session doReadSession(Serializable sessionId) {
        String sql = "select session from sessions where id=?";
        List<String> sessionStrList = jdbcTemplate.queryForList(sql, String.class, sessionId);
        if(sessionStrList.size() == 0) return null;
        return SerializableUtils.deserialize(sessionStrList.get(0));
    }
}
```

doCreate/doUpdate/doDelete/doReadSession 分别代表创建 / 修改 / 删除 / 读取会话；此处通过把会话序列化后存储到数据库实现；接着在 shiro-web.ini 中配置：

```ini
sessionDAO=com.github.zhangkaitao.shiro.chapter10.session.dao.MySessionDAO
```

其他设置和之前一样，因为继承了 CachingSessionDAO；所有在读取时会先查缓存中是否存在，如果找不到才到数据库中查找。

## 会话验证

Shiro 提供了会话验证调度器，用于定期的验证会话是否已过期，如果过期将停止会话；出于性能考虑，一般情况下都是获取会话时来验证会话是否过期并停止会话的；但是如在 web 环境中，如果用户不主动退出是不知道会话是否过期的，因此需要定期的检测会话是否过期，Shiro 提供了会话验证调度器 SessionValidationScheduler 来做这件事情。

可以通过如下 ini 配置开启会话验证：

```ini
sessionValidationScheduler=org.apache.shiro.session.mgt.ExecutorServiceSessionValidationScheduler
sessionValidationScheduler.interval = 3600000
sessionValidationScheduler.sessionManager=$sessionManager
sessionManager.globalSessionTimeout=1800000
sessionManager.sessionValidationSchedulerEnabled=true
sessionManager.sessionValidationScheduler=$sessionValidationScheduler
```

- sessionValidationScheduler：会话验证调度器，sessionManager 默认就是使用 ExecutorServiceSessionValidationScheduler，其使用 JDK 的 ScheduledExecutorService 进行定期调度并验证会话是否过期；
- sessionValidationScheduler.interval：设置调度时间间隔，单位毫秒，默认就是 1 小时；
- sessionValidationScheduler.sessionManager：设置会话验证调度器进行会话验证时的会话管理器；
- sessionManager.globalSessionTimeout：设置全局会话超时时间，默认 30 分钟，即如果 30 分钟内没有访问会话将过期；
- sessionManager.sessionValidationSchedulerEnabled：是否开启会话验证器，默认是开启的；
- sessionManager.sessionValidationScheduler：设置会话验证调度器，默认就是使用 ExecutorServiceSessionValidationScheduler。

Shiro 也提供了使用 Quartz 会话验证调度器：

```ini
sessionValidationScheduler=org.apache.shiro.session.mgt.quartz.QuartzSessionValidationScheduler
sessionValidationScheduler.sessionValidationInterval = 3600000
sessionValidationScheduler.sessionManager=$sessionManager
```

使用时需要导入 shiro-quartz 依赖：

```xml
<dependency>
     <groupId>org.apache.shiro</groupId>
     <artifactId>shiro-quartz</artifactId>
     <version>1.2.2</version>
</dependency>
```

如上会话验证调度器实现都是直接调用 AbstractValidatingSessionManager 的 validateSessions 方法进行验证，其直接调用 SessionDAO 的 getActiveSessions 方法获取所有会话进行验证，如果会话比较多，会影响性能；可以考虑如分页获取会话并进行验证，如 com.github.zhangkaitao.shiro.chapter10.session.scheduler.MySessionValidationScheduler：

```java
//分页获取会话并验证
String sql = "select session from sessions limit ?,?";
int start = 0; //起始记录
int size = 20; //每页大小
List<String> sessionList = jdbcTemplate.queryForList(sql, String.class, start, size);
while(sessionList.size() > 0) {
  for(String sessionStr : sessionList) {
    try {
      Session session = SerializableUtils.deserialize(sessionStr);
      Method validateMethod = 
        ReflectionUtils.findMethod(AbstractValidatingSessionManager.class, 
            "validate", Session.class, SessionKey.class);
      validateMethod.setAccessible(true);
      ReflectionUtils.invokeMethod(validateMethod, 
        sessionManager, session, new DefaultSessionKey(session.getId()));
    } catch (Exception e) {
        //ignore
    }
  }
 start = start + size;
  sessionList = jdbcTemplate.queryForList(sql, String.class, start, size);
}
```

其直接改造自 ExecutorServiceSessionValidationScheduler，如上代码是验证的核心代码，可以根据自己的需求改造此验证调度器器；ini 的配置和之前的类似。

如果在会话过期时不想删除过期的会话，可以通过如下 ini 配置进行设置：

```ini
sessionManager.deleteInvalidSessions=false
```

默认是开启的，在会话过期后会调用 SessionDAO 的 delete 方法删除会话：如会话时持久化存储的，可以调用此方法进行删除。

如果是在获取会话时验证了会话已过期，将抛出 InvalidSessionException；因此需要捕获这个异常并跳转到相应的页面告诉用户会话已过期，让其重新登录，如可以在 web.xml 配置相应的错误页面：

```xml
<error-page>
    <exception-type>org.apache.shiro.session.InvalidSessionException</exception-type>
    <location>/invalidSession.jsp</location>
</error-page>
```

## sessionFactory

sessionFactory 是创建会话的工厂，根据相应的 Subject 上下文信息来创建会话；默认提供了 SimpleSessionFactory 用来创建 SimpleSession 会话。

首先自定义一个 Session：

```java
public class OnlineSession extends SimpleSession {
    public static enum OnlineStatus {
        on_line("在线"), hidden("隐身"), force_logout("强制退出");
        private final String info;
        private OnlineStatus(String info) {
            this.info = info;
        }
        public String getInfo() {
            return info;
        }
    }
    private String userAgent; //用户浏览器类型
    private OnlineStatus status = OnlineStatus.on_line; //在线状态
    private String systemHost; //用户登录时系统IP
    //省略其他
}
```

OnlineSession 用于保存当前登录用户的在线状态，支持如离线等状态的控制。

接着自定义 SessionFactory：

```java
public class OnlineSessionFactory implements SessionFactory {
    @Override
    public Session createSession(SessionContext initData) {
        OnlineSession session = new OnlineSession();
        if (initData != null && initData instanceof WebSessionContext) {
            WebSessionContext sessionContext = (WebSessionContext) initData;
            HttpServletRequest request = (HttpServletRequest) sessionContext.getServletRequest();
            if (request != null) {
                session.setHost(IpUtils.getIpAddr(request));
                session.setUserAgent(request.getHeader("User-Agent"));
                session.setSystemHost(request.getLocalAddr() + ":" + request.getLocalPort());
            }
        }
        return session;
    }
}
```

根据会话上下文创建相应的 OnlineSession。

最后在 shiro-web.ini 配置文件中配置：

```ini
sessionFactory=org.apache.shiro.session.mgt.OnlineSessionFactory
sessionManager.sessionFactory=$sessionFactory
```

# 9、Shiro 缓存机制

> 我们到后面的学习会使用我们的Redis来进行缓存管理

## 缓存机制

Shiro 提供了类似于 Spring 的 Cache 抽象，即 Shiro 本身不实现 Cache，但是对 Cache 进行了又抽象，方便更换不同的底层 Cache 实现。对于 Cache 的一些概念可以参考我的《Spring Cache 抽象详解》：http://jinnianshilongnian.iteye.com/blog/2001040。

**Shiro 提供的 Cache 接口**：

```java
public interface Cache<K, V> {
    //根据Key获取缓存中的值
    public V get(K key) throws CacheException;
    //往缓存中放入key-value，返回缓存中之前的值
    public V put(K key, V value) throws CacheException; 
    //移除缓存中key对应的值，返回该值
    public V remove(K key) throws CacheException;
    //清空整个缓存
    public void clear() throws CacheException;
    //返回缓存大小
    public int size();
    //获取缓存中所有的key
    public Set<K> keys();
    //获取缓存中所有的value
    public Collection<V> values();
}
```

**Shiro 提供的 CacheManager 接口**：

```java
public interface CacheManager {
    //根据缓存名字获取一个Cache
    public <K, V> Cache<K, V> getCache(String name) throws CacheException;
}
```

**Shiro 还提供了 CacheManagerAware 用于注入 CacheManager**：

```java
public interface CacheManagerAware {
    //注入CacheManager
    void setCacheManager(CacheManager cacheManager);
}
```

Shiro 内部相应的组件（DefaultSecurityManager）会自动检测相应的对象（如 Realm）是否实现了 CacheManagerAware 并自动注入相应的 CacheManager。

本章用例使用了与第六章的代码。

## Realm 缓存

Shiro 提供了 CachingRealm，其实现了 CacheManagerAware 接口，提供了缓存的一些基础实现；另外 AuthenticatingRealm 及 AuthorizingRealm 分别提供了对 AuthenticationInfo 和 AuthorizationInfo 信息的缓存。

**ini 配置**

```ini
userRealm=com.github.zhangkaitao.shiro.chapter11.realm.UserRealm
userRealm.credentialsMatcher=$credentialsMatcher
userRealm.cachingEnabled=true
userRealm.authenticationCachingEnabled=true
userRealm.authenticationCacheName=authenticationCache
userRealm.authorizationCachingEnabled=true
userRealm.authorizationCacheName=authorizationCache
securityManager.realms=$userRealm
cacheManager=org.apache.shiro.cache.ehcache.EhCacheManager
cacheManager.cacheManagerConfigFile=classpath:shiro-ehcache.xml
securityManager.cacheManager=$cacheManager
```

- userRealm.cachingEnabled：启用缓存，默认 false；
- userRealm.authenticationCachingEnabled：启用身份验证缓存，即缓存 AuthenticationInfo 信息，默认 false；
- userRealm.authenticationCacheName：缓存 AuthenticationInfo 信息的缓存名称；
- userRealm. authorizationCachingEnabled：启用授权缓存，即缓存 AuthorizationInfo 信息，默认 false；
- userRealm. authorizationCacheName：缓存 AuthorizationInfo 信息的缓存名称；
- cacheManager：缓存管理器，此处使用 EhCacheManager，即 Ehcache 实现，需要导入相应的 Ehcache 依赖，请参考 pom.xml；

因为测试用例的关系，需要将 Ehcache 的 CacheManager 改为使用 VM 单例模式： this.manager = new net.sf.ehcache.CacheManager(getCacheManagerConfigFileInputStream())； 改为 this.manager = net.sf.ehcache.CacheManager.create(getCacheManagerConfigFileInputStream())；

**测试用例**

```java
@Test
public void testClearCachedAuthenticationInfo() {
    login(u1.getUsername(), password);
    userService.changePassword(u1.getId(), password + "1");
    RealmSecurityManager securityManager =
     (RealmSecurityManager) SecurityUtils.getSecurityManager();
    UserRealm userRealm = (UserRealm) securityManager.getRealms().iterator().next();   userRealm.clearCachedAuthenticationInfo(subject().getPrincipals());
    login(u1.getUsername(), password + "1");
}
```

首先登录成功（此时会缓存相应的 AuthenticationInfo），然后修改密码；此时密码就变了；接着需要调用 Realm 的 clearCachedAuthenticationInfo 方法清空之前缓存的 AuthenticationInfo；否则下次登录时还会获取到修改密码之前的那个 AuthenticationInfo；

```java
@Test
public void testClearCachedAuthorizationInfo() {
    login(u1.getUsername(), password);
    subject().checkRole(r1.getRole());
    userService.correlationRoles(u1.getId(), r2.getId());
    RealmSecurityManager securityManager =
      (RealmSecurityManager) SecurityUtils.getSecurityManager();
    UserRealm userRealm = (UserRealm)securityManager.getRealms().iterator().next();   userRealm.clearCachedAuthorizationInfo(subject().getPrincipals());
    subject().checkRole(r2.getRole());
}
```

和之前的用例差不多；此处调用 Realm 的 clearCachedAuthorizationInfo 清空之前缓存的 AuthorizationInfo；

另外还有 clearCache，其同时调用 clearCachedAuthenticationInfo 和 clearCachedAuthorizationInfo，清空 AuthenticationInfo 和 AuthorizationInfo。

UserRealm 还提供了 clearAllCachedAuthorizationInfo、clearAllCachedAuthenticationInfo、clearAllCache，用于清空整个缓存。

在某些清空下这种方式可能不是最好的选择，可以考虑直接废弃 Shiro 的缓存，然后自己通过如 AOP 机制实现自己的缓存；可以参考： https://github.com/zhangkaitao/es/tree/master/web/src/main/java/com/sishuok/es/extra/aop

另外如果和 Spring 集成时可以考虑直接使用 Spring 的 Cache 抽象，可以考虑使用 SpringCacheManagerWrapper，其对 Spring Cache 进行了包装，转换为 Shiro 的 CacheManager 实现：
https://github.com/zhangkaitao/es/blob/master/web/src/main/java/org/apache/shiro/cache/spring/SpringCacheManagerWrapper.java

## Session 缓存

当我们设置了 SecurityManager 的 CacheManager 时，如：

```ini
securityManager.cacheManager=$cacheManager
```

当我们设置 SessionManager 时：

```ini
sessionManager=org.apache.shiro.session.mgt.DefaultSessionManager
securityManager.sessionManager=$sessionManager
```

如 securityManager 实现了 SessionsSecurityManager，其会自动判断 SessionManager 是否实现了 CacheManagerAware 接口，如果实现了会把 CacheManager 设置给它。然后 sessionManager 会判断相应的 sessionDAO（如继承自 CachingSessionDAO）是否实现了 CacheManagerAware，如果实现了会把 CacheManager 设置给它；如第九章的 MySessionDAO 就是带缓存的 SessionDAO；其会先查缓存，如果找不到才查数据库。

对于 CachingSessionDAO，可以通过如下配置设置缓存的名称：

```ini
sessionDAO=com.github.zhangkaitao.shiro.chapter11.session.dao.MySessionDAO
sessionDAO.activeSessionsCacheName=shiro-activeSessionCache
```

activeSessionsCacheName 默认就是 shiro-activeSessionCache。

# 10、Shiro Spring 集成

## 与 Spring集成

Shiro 的组件都是 JavaBean/POJO 式的组件，所以非常容易使用 Spring 进行组件管理，可以非常方便的从 ini 配置迁移到 Spring 进行管理，且支持 JavaSE 应用及 Web 应用的集成。

在示例之前，需要导入 shiro-spring 及 spring-context 依赖，具体请参考 pom.xml。
spring-beans.xml 配置文件提供了基础组件如 DataSource、DAO、Service 组件的配置。

## JavaSE 应用

spring-shiro.xml 提供了普通 JavaSE 独立应用的 Spring 配置：

```xml
<!-- 缓存管理器 使用Ehcache实现 -->
<bean id="cacheManager" class="org.apache.shiro.cache.ehcache.EhCacheManager">
    <property name="cacheManagerConfigFile" value="classpath:ehcache.xml"/>
</bean>
<!-- 凭证匹配器 -->
<bean id="credentialsMatcher" class="
com.github.zhangkaitao.shiro.chapter12.credentials.RetryLimitHashedCredentialsMatcher">
    <constructor-arg ref="cacheManager"/>
    <property name="hashAlgorithmName" value="md5"/>
    <property name="hashIterations" value="2"/>
    <property name="storedCredentialsHexEncoded" value="true"/>
</bean>
<!-- Realm实现 -->
<bean id="userRealm" class="com.github.zhangkaitao.shiro.chapter12.realm.UserRealm">
    <property name="userService" ref="userService"/>
    <property name="credentialsMatcher" ref="credentialsMatcher"/>
    <property name="cachingEnabled" value="true"/>
    <property name="authenticationCachingEnabled" value="true"/>
    <property name="authenticationCacheName" value="authenticationCache"/>
    <property name="authorizationCachingEnabled" value="true"/>
    <property name="authorizationCacheName" value="authorizationCache"/>
</bean>
<!-- 会话ID生成器 -->
<bean id="sessionIdGenerator" 
class="org.apache.shiro.session.mgt.eis.JavaUuidSessionIdGenerator"/>
<!-- 会话DAO -->
<bean id="sessionDAO" 
class="org.apache.shiro.session.mgt.eis.EnterpriseCacheSessionDAO">
    <property name="activeSessionsCacheName" value="shiro-activeSessionCache"/>
    <property name="sessionIdGenerator" ref="sessionIdGenerator"/>
</bean>
<!-- 会话验证调度器 -->
<bean id="sessionValidationScheduler" 
class="org.apache.shiro.session.mgt.quartz.QuartzSessionValidationScheduler">
    <property name="sessionValidationInterval" value="1800000"/>
    <property name="sessionManager" ref="sessionManager"/>
</bean>
<!-- 会话管理器 -->
<bean id="sessionManager" class="org.apache.shiro.session.mgt.DefaultSessionManager">
    <property name="globalSessionTimeout" value="1800000"/>
    <property name="deleteInvalidSessions" value="true"/>
    <property name="sessionValidationSchedulerEnabled" value="true"/>
   <property name="sessionValidationScheduler" ref="sessionValidationScheduler"/>
    <property name="sessionDAO" ref="sessionDAO"/>
</bean>
<!-- 安全管理器 -->
<bean id="securityManager" class="org.apache.shiro.mgt.DefaultSecurityManager">
    <property name="realms">
        <list><ref bean="userRealm"/></list>
    </property>
    <property name="sessionManager" ref="sessionManager"/>
    <property name="cacheManager" ref="cacheManager"/>
</bean>
<!-- 相当于调用SecurityUtils.setSecurityManager(securityManager) -->
<bean class="org.springframework.beans.factory.config.MethodInvokingFactoryBean">
<property name="staticMethod" 
value="org.apache.shiro.SecurityUtils.setSecurityManager"/>
    <property name="arguments" ref="securityManager"/>
</bean>
<!-- Shiro生命周期处理器-->
<bean id="lifecycleBeanPostProcessor" 
class="org.apache.shiro.spring.LifecycleBeanPostProcessor"/>
```

可以看出，只要把之前的 ini 配置翻译为此处的 spring xml 配置方式即可，无须多解释。 LifecycleBeanPostProcessor 用于在实现了 Initializable 接口的 Shiro bean 初始化时调用 Initializable 接口回调，在实现了 Destroyable 接口的 Shiro bean 销毁时调用 Destroyable 接口回调。如 UserRealm 就实现了 Initializable，而 DefaultSecurityManager 实现了 Destroyable。具体可以查看它们的继承关系。

测试用例请参考 com.github.zhangkaitao.shiro.chapter12.ShiroTest。

## Web 应用

Web 应用和普通 JavaSE 应用的某些配置是类似的，此处只提供一些不一样的配置，详细配置可以参考 spring-shiro-web.xml。

```xml
<!-- 会话Cookie模板 -->
<bean id="sessionIdCookie" class="org.apache.shiro.web.servlet.SimpleCookie">
    <constructor-arg value="sid"/>
    <property name="httpOnly" value="true"/>
    <property name="maxAge" value="180000"/>
</bean>
<!-- 会话管理器 -->
<bean id="sessionManager" 
class="org.apache.shiro.web.session.mgt.DefaultWebSessionManager">
    <property name="globalSessionTimeout" value="1800000"/>
    <property name="deleteInvalidSessions" value="true"/>
    <property name="sessionValidationSchedulerEnabled" value="true"/>
    <property name="sessionValidationScheduler" ref="sessionValidationScheduler"/>
    <property name="sessionDAO" ref="sessionDAO"/>
    <property name="sessionIdCookieEnabled" value="true"/>
    <property name="sessionIdCookie" ref="sessionIdCookie"/>
</bean>
<!-- 安全管理器 -->
<bean id="securityManager" class="org.apache.shiro.web.mgt.DefaultWebSecurityManager">
<property name="realm" ref="userRealm"/>
    <property name="sessionManager" ref="sessionManager"/>
    <property name="cacheManager" ref="cacheManager"/>
</bean>
```

1. sessionIdCookie 是用于生产 Session ID Cookie 的模板；
2. 会话管理器使用用于 web 环境的 DefaultWebSessionManager；
3. 安全管理器使用用于 web 环境的 DefaultWebSecurityManager。

```xml
<!-- 基于Form表单的身份验证过滤器 -->
<bean id="formAuthenticationFilter" 
class="org.apache.shiro.web.filter.authc.FormAuthenticationFilter">
    <property name="usernameParam" value="username"/>
    <property name="passwordParam" value="password"/>
    <property name="loginUrl" value="/login.jsp"/>
</bean>
<!-- Shiro的Web过滤器 -->
<bean id="shiroFilter" class="org.apache.shiro.spring.web.ShiroFilterFactoryBean">
    <property name="securityManager" ref="securityManager"/>
    <property name="loginUrl" value="/login.jsp"/>
    <property name="unauthorizedUrl" value="/unauthorized.jsp"/>
    <property name="filters">
        <util:map>
            <entry key="authc" value-ref="formAuthenticationFilter"/>
        </util:map>
    </property>
    <property name="filterChainDefinitions">
        <value>
            /index.jsp = anon
            /unauthorized.jsp = anon
            /login.jsp = authc
            /logout = logout
            /** = user
        </value>
    </property>
</bean>
```

1. formAuthenticationFilter 为基于 Form 表单的身份验证过滤器；此处可以再添加自己的 Filter bean 定义；
2. shiroFilter：此处使用 ShiroFilterFactoryBean 来创建 ShiroFilter 过滤器；filters 属性用于定义自己的过滤器，即 ini 配置中的 [filters] 部分；filterChainDefinitions 用于声明 url 和 filter 的关系，即 ini 配置中的 [urls] 部分。

接着需要在 web.xml 中进行如下配置：

```xml
<context-param>
    <param-name>contextConfigLocation</param-name>
    <param-value>
        classpath:spring-beans.xml,
        classpath:spring-shiro-web.xml
    </param-value>
</context-param>
<listener>
   <listener-class>
org.springframework.web.context.ContextLoaderListener
</listener-class>
</listener>
```

通过 ContextLoaderListener 加载 contextConfigLocation 指定的 Spring 配置文件。

```xml
<filter>
    <filter-name>shiroFilter</filter-name>
    <filter-class>org.springframework.web.filter.DelegatingFilterProxy</filter-class>
    <init-param>
        <param-name>targetFilterLifecycle</param-name>
        <param-value>true</param-value>
    </init-param>
</filter>
<filter-mapping>
    <filter-name>shiroFilter</filter-name>
    <url-pattern>/*</url-pattern>
</filter-mapping>
```

DelegatingFilterProxy 会自动到 Spring 容器中查找名字为 shiroFilter 的 bean 并把 filter 请求交给它处理。

其他配置请参考源代码。

## Shiro 权限注解

Shiro 提供了相应的注解用于权限控制，如果使用这些注解就需要使用 AOP 的功能来进行判断，如 Spring AOP；Shiro 提供了 Spring AOP 集成用于权限注解的解析和验证。

为了测试，此处使用了 Spring MVC 来测试 Shiro 注解，当然 Shiro 注解不仅仅可以在 web 环境使用，在独立的 JavaSE 中也是可以用的，此处只是以 web 为例了。

在 spring-mvc.xml 配置文件添加 Shiro Spring AOP 权限注解的支持：

```xml
<aop:config proxy-target-class="true"></aop:config>
<bean class="
org.apache.shiro.spring.security.interceptor.AuthorizationAttributeSourceAdvisor">
    <property name="securityManager" ref="securityManager"/>
</bean>
```

如上配置用于开启 Shiro Spring AOP 权限注解的支持；`<aop:config proxy-target-class="true">` 表示代理类。

接着就可以在相应的控制器（AnnotationController）中使用如下方式进行注解：

```java
@RequiresRoles("admin")
@RequestMapping("/hello2")
public String hello2() {
    return "success";
}
```

访问 hello2 方法的前提是当前用户有 admin 角色。

当验证失败，其会抛出 UnauthorizedException 异常，此时可以使用 Spring 的 ExceptionHandler（DefaultExceptionHandler）来进行拦截处理：

```java
@ExceptionHandler({UnauthorizedException.class})
@ResponseStatus(HttpStatus.UNAUTHORIZED)
public ModelAndView processUnauthenticatedException(NativeWebRequest request, UnauthorizedException e) {
    ModelAndView mv = new ModelAndView();
    mv.addObject("exception", e);
    mv.setViewName("unauthorized");
    return mv;
}
```

如果集成 Struts2，需要注意《Shiro+Struts2+Spring3 加上 @RequiresPermissions 后 @Autowired 失效》问题：
http://jinnianshilongnian.iteye.com/blog/1850425

**权限注解**

```java
@RequiresAuthentication
```

表示当前 Subject 已经通过 login 进行了身份验证；即 Subject.isAuthenticated() 返回 true。

```java
@RequiresUser
```

表示当前 Subject 已经身份验证或者通过记住我登录的。

```java
@RequiresGuest
```

表示当前 Subject 没有身份验证或通过记住我登录过，即是游客身份。

```java
@RequiresRoles(value={“admin”, “user”}, logical= Logical.AND)
```

表示当前 Subject 需要角色 admin 和 user。

```java
@RequiresPermissions (value={“user:a”, “user:b”}, logical= Logical.OR)
```

表示当前 Subject 需要权限 user：a 或 user：b。

# 11、Shiro RememberMe

## RememberMe

Shiro 提供了记住我（RememberMe）的功能，比如访问如淘宝等一些网站时，关闭了浏览器下次再打开时还是能记住你是谁，下次访问时无需再登录即可访问，基本流程如下：

1. 首先在登录页面选中 RememberMe 然后登录成功；如果是浏览器登录，一般会把 RememberMe 的 Cookie 写到客户端并保存下来；
2. 关闭浏览器再重新打开；会发现浏览器还是记住你的；
3. 访问一般的网页服务器端还是知道你是谁，且能正常访问；
4. 但是比如我们访问淘宝时，如果要查看我的订单或进行支付时，此时还是需要再进行身份认证的，以确保当前用户还是你。

## RememberMe 配置

**spring-shiro-web.xml 配置**：

```xml
<bean id="sessionIdCookie" class="org.apache.shiro.web.servlet.SimpleCookie">
    <constructor-arg value="sid"/>
    <property name="httpOnly" value="true"/>
    <property name="maxAge" value="-1"/>
</bean>
<bean id="rememberMeCookie" class="org.apache.shiro.web.servlet.SimpleCookie">
    <constructor-arg value="rememberMe"/>
    <property name="httpOnly" value="true"/>
    <property name="maxAge" value="2592000"/><!-- 30天 -->
</bean>
```

- sessionIdCookie：maxAge=-1 表示浏览器关闭时失效此 Cookie；
- rememberMeCookie：即记住我的 Cookie，保存时长 30 天；

```xml
`<!-- rememberMe管理器 -->`
<bean id="rememberMeManager" 
class="org.apache.shiro.web.mgt.CookieRememberMeManager">
    <property name="cipherKey" value="
\#{T(org.apache.shiro.codec.Base64).decode('4AvVhmFLUs0KTA3Kprsdag==')}"/>
     <property name="cookie" ref="rememberMeCookie"/>
</bean>
```

rememberMe 管理器，cipherKey 是加密 rememberMe Cookie 的密钥；默认 AES 算法；

```xml
`<!-- 安全管理器 -->`
<bean id="securityManager" class="org.apache.shiro.web.mgt.DefaultWebSecurityManager">
    ……
  <property name="rememberMeManager" ref="rememberMeManager"/>
</bean>
```

设置 securityManager 安全管理器的 rememberMeManager；

```xml
<bean id="formAuthenticationFilter" 
class="org.apache.shiro.web.filter.authc.FormAuthenticationFilter">
    ……
    <property name="rememberMeParam" value="rememberMe"/>
</bean>
```

rememberMeParam，即 rememberMe 请求参数名，请求参数是 boolean 类型，true 表示 rememberMe。

```xml
<bean id="shiroFilter" class="org.apache.shiro.spring.web.ShiroFilterFactoryBean">
    ……
    <property name="filterChainDefinitions">
        <value>
            /login.jsp = authc
            /logout = logout
            /authenticated.jsp = authc
            /** = user
        </value>
    </property>
</bean>
```

“/authenticated.jsp = authc” 表示访问该地址用户必须身份验证通过（Subject. isAuthenticated()==true）；而 “/** = user” 表示访问该地址的用户是身份验证通过或 RememberMe 登录的都可以。

**测试**：

1. 访问 `http://localhost:8080/chapter13/`，会跳转到登录页面，登录成功后会设置会话及 rememberMe Cookie；
2. 关闭浏览器，此时会话 cookie 将失效；
3. 然后重新打开浏览器访问 `http://localhost:8080/chapter13/`，还是可以访问的；
4. 如果此时访问 `http://localhost:8080/chapter13/authenticated.jsp`，会跳转到登录页面重新进行身份验证。

如果要自己做 RememeberMe，需要在登录之前这样创建 Token：UsernamePasswordToken(用户名，密码，是否记住我)，如：

```java
Subject subject = SecurityUtils.getSubject();
UsernamePasswordToken token = new UsernamePasswordToken(username, password);
token.setRememberMe(true);
subject.login(token);
```

subject.isAuthenticated() 表示用户进行了身份验证登录的，即使有 Subject.login 进行了登录； subject.isRemembered()：表示用户是通过记住我登录的，此时可能并不是真正的你（如你的朋友使用你的电脑，或者你的 cookie 被窃取）在访问的；且两者二选一，即 subject.isAuthenticated()==true，则 subject.isRemembered()==false；反之一样。

另外对于过滤器，一般这样使用：
**访问一般网页**，如个人在主页之类的，我们使用 user 拦截器即可，user 拦截器只要用户登录 (isRemembered()==true or isAuthenticated()==true) 过即可访问成功；
**访问特殊网页**，如我的订单，提交订单页面，我们使用 authc 拦截器即可，authc 拦截器会判断用户是否是通过 Subject.login（isAuthenticated()==true）登录的，如果是才放行，否则会跳转到登录页面叫你重新登录。

因此 RememberMe 使用过程中，需要配合相应的拦截器来实现相应的功能，用错了拦截器可能就不能满足你的需求了。

# 12、Shiro SSL (了解)

2020-12-04 09:43 更新

## SSL

对于 SSL 的支持，Shiro 只是判断当前 url 是否需要 SSL 登录，如果需要自动重定向到 https 进行访问。

**首先生成数字证书，生成证书到 D:\localhost.keystore**
使用 JDK 的 keytool 命令，生成证书（包含证书 / 公钥 / 私钥）到 `D:\localhost.keystore`：

```
keytool -genkey -keystore "D:\localhost.keystore" -alias localhost -keyalg RSA
输入密钥库口令:
再次输入新口令:
您的名字与姓氏是什么?
  [Unknown]:  localhost
您的组织单位名称是什么?
  [Unknown]:  sishuok.com
您的组织名称是什么?
  [Unknown]:  sishuok.com
您所在的城市或区域名称是什么?
  [Unknown]:  beijing
您所在的省/市/自治区名称是什么?
  [Unknown]:  beijing
该单位的双字母国家/地区代码是什么?
  [Unknown]:  cn
CN=localhost, OU=sishuok.com, O=sishuok.com, L=beijing, ST=beijing, C=cn是否正确
?
  [否]:  y

输入 <localhost> 的密钥口令
        (如果和密钥库口令相同, 按回车):
再次输入新口令:
```

通过如上步骤，生成证书到 `D:\ localhost.keystore`；

**然后设置 tomcat 下的 server.xml**

此处使用了 apache-tomcat-7.0.40 版本，打开 conf/server.xml，找到：

```xml
\<!--
<Connector port="8443" protocol="HTTP/1.1" SSLEnabled="true"
       maxThreads="150" scheme="https" secure="true"
       clientAuth="false" sslProtocol="TLS" />
\-->
```

替换为

```xml
<Connector port="8443" protocol="HTTP/1.1" SSLEnabled="true"
       maxThreads="150" scheme="https" secure="true"
       clientAuth="false" sslProtocol="TLS" 
       keystoreFile="D:\localhost.keystore" keystorePass="123456"/>
```

keystorePass 就是生成 keystore 时设置的密码。

**添加 SSL 到配置文件（spring-shiro-web.xml）**

此处使用了和十三章一样的代码：

```xml
<bean id="sslFilter" class="org.apache.shiro.web.filter.authz.SslFilter">
    <property name="port" value="8443"/>
</bean>
<bean id="shiroFilter" class="org.apache.shiro.spring.web.ShiroFilterFactoryBean">
    ……
    <property name="filters">
        <util:map>
            <entry key="authc" value-ref="formAuthenticationFilter"/>
            <entry key="ssl" value-ref="sslFilter"/>
        </util:map>
    </property>
    <property name="filterChainDefinitions">
        <value>
            /login.jsp = ssl,authc
            /logout = logout
            /authenticated.jsp = authc
            /** = user
        </value>
    </property>
</bean>
```

SslFilter 默认端口是 443，此处使用了 8443；“/login.jsp = ssl,authc” 表示访问登录页面时需要走 SSL。

**测试**

最后把 shiro-example-chapter14 打成 war 包（mvn:package），放到 tomcat 下的 webapps 中，启动服务器测试，如访问 localhost:9080/chapter14/，会自动跳转到 https://localhost:8443/chapter14/login.jsp。

如果使用 Maven Jetty 插件，可以直接如下插件配置：

```xml
<plugin>
   <groupId>org.mortbay.jetty</groupId>
   <artifactId>jetty-maven-plugin</artifactId>
   <version>8.1.8.v20121106</version>
   <configuration>
     <webAppConfig>
       <contextPath>/${project.build.finalName}</contextPath>
     </webAppConfig>
     <connectors>
     <connector implementation="org.eclipse.jetty.server.nio.SelectChannelConnector">
       <port>8080</port>
     </connector>
     <connector implementation="org.eclipse.jetty.server.ssl.SslSocketConnector">
       <port>8443</port>
       <keystore>${project.basedir}/localhost.keystore</keystore>
       <password>123456</password>
       <keyPassword>123456</keyPassword>
     </connector>
     </connectors>
   </configuration>
</plugin>
```

# 13、Shiro 单点登录 (了解)

## 单点登录

Shiro 1.2 开始提供了 Jasig CAS 单点登录的支持，单点登录主要用于多系统集成，即在多个系统中，用户只需要到一个中央服务器登录一次即可访问这些系统中的任何一个，无须多次登录。此处我们使用 Jasig CAS v4.0.0-RC3 版本：
https://github.com/Jasig/cas/tree/v4.0.0-RC3

Jasig CAS 单点登录系统分为服务器端和客户端，服务器端提供单点登录，多个客户端（子系统）将跳转到该服务器进行登录验证，大体流程如下：

1. 访问客户端需要登录的页面 `http://localhost:9080/client/`，此时会跳到单点登录服务器 `https://localhost:8443/server/login?service=https://localhost:9443/client/cas`；
2. 如果此时单点登录服务器也没有登录的话，会显示登录表单页面，输入用户名 / 密码进行登录；
3. 登录成功后服务器端会回调客户端传入的地址：`https://localhost:9443/client/cas?ticket=ST-1-eh2cIo92F9syvoMs5DOg-cas01.example.org`，且带着一个 ticket；
4. 客户端会把 ticket 提交给服务器来验证 ticket 是否有效；如果有效服务器端将返回用户身份；
5. 客户端可以再根据这个用户身份获取如当前系统用户 / 角色 / 权限信息。

本章使用了和《第十四章 SSL》一样的数字证书。

## 服务器端

我们使用了 Jasig CAS 服务器 v4.0.0-RC3 版本，可以到其官方的 github 下载：`https://github.com/Jasig/cas/tree/v4.0.0-RC3` 下载，然后将其 cas-server-webapp 模块封装到 shiro-example-chapter15-server 模块中，具体请参考源码。

1、数字证书使用和《第十四章 SSL》一样的数字证书，即将 localhost.keystore 拷贝到 shiro-example-chapter15-server 模块根目录下；

2、在 pom.xml 中添加 Jetty Maven 插件，并添加 SSL 支持：

```xml
<plugin>
  <groupId>org.mortbay.jetty</groupId>
  <artifactId>jetty-maven-plugin</artifactId>
  <version>8.1.8.v20121106</version>
  <configuration>
    <webAppConfig>
      <contextPath>/${project.build.finalName}</contextPath>
    </webAppConfig>
    <connectors>
      <connector implementation="org.eclipse.jetty.server.nio.SelectChannelConnector">
        <port>8080</port>
      </connector>
      <connector implementation="org.eclipse.jetty.server.ssl.SslSocketConnector">
        <port>8443</port>
        <keystore>${project.basedir}/localhost.keystore</keystore>
       <password>123456</password>
        <keyPassword>123456</keyPassword>
      </connector>
    </connectors>
  </configuration>
</plugin>
```

3、修改 `src/main/webapp/WEB-INF/deployerConfigContext.xml`，找到 primaryAuthenticationHandler，然后添加一个账户：

```xml
<entry key="zhang" value="123"/>
```

其也支持如 JDBC 查询，可以自己定制；具体请参考文档。

4、mvn jetty:run 启动服务器测试即可：
访问 `https://localhost:8443/chapter15-server/login` 将弹出如下登录页面：

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/17.png)

输入用户名 / 密码，如 zhang/123，将显示登录成功页面：

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/18.png)

到此服务器端的简单配置就完成了。

## 客户端

1、首先使用 localhost.keystore 导出数字证书（公钥）到 `D:\localhost.cer`

```sh
keytool -export -alias localhost -file D:\localhost.cer -keystore D:\localhost.keystore 
```

2、因为 CAS client 需要使用该证书进行验证，需要将证书导入到 JDK 中：

```sh
cd D:\jdk1.7.0_21\jre\lib\security
keytool -import -alias localhost -file D:\localhost.cer -noprompt -trustcacerts -storetype jks -keystore cacerts -storepass 123456
```

如果导入失败，可以先把 security 目录下的 cacerts 删掉；

3、按照服务器端的 Jetty Maven 插件的配置方式配置 Jetty 插件；

4、在 shiro-example-chapter15-client 模块中导入 shiro-cas 依赖，具体请参考其 pom.xml；

5、自定义 CasRealm：

```java
public class MyCasRealm extends CasRealm {
    private UserService userService;
    public void setUserService(UserService userService) {
        this.userService = userService;
    }
    @Override
    protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principals) {
        String username = (String)principals.getPrimaryPrincipal();
        SimpleAuthorizationInfo authorizationInfo = new SimpleAuthorizationInfo();
        authorizationInfo.setRoles(userService.findRoles(username));
        authorizationInfo.setStringPermissions(userService.findPermissions(username));
        return authorizationInfo;
    }
}
```

CasRealm 根据 CAS 服务器端返回的用户身份获取相应的角色 / 权限信息。

6、spring-shiro-web.xml 配置：

```xml
<bean id="casRealm" class="com.github.zhangkaitao.shiro.chapter13.realm.MyCasRealm">
    <property name="userService" ref="userService"/>
    ……
    <property name="casServerUrlPrefix" value="https://localhost:8443/chapter14-server"/>
    <property name="casService" value="https://localhost:9443/chapter14-client/cas"/>
</bean>
```

casServerUrlPrefix：是 CAS Server 服务器端地址；
casService：是当前应用 CAS 服务 URL，即用于接收并处理登录成功后的 Ticket 的；

如果角色 / 权限信息是由服务器端提供的话，我们可以直接使用 CasRealm：

```xml
<bean id="casRealm" class="org.apache.shiro.cas.CasRealm">
    ……
    <property name="defaultRoles" value="admin,user"/>
    <property name="defaultPermissions" value="user:create,user:update"/>
    <property name="roleAttributeNames" value="roles"/>
    <property name="permissionAttributeNames" value="permissions"/>
    <property name="casServerUrlPrefix" value="https://localhost:8443/chapter14-server"/>
    <property name="casService" value="https://localhost:9443/chapter14-client/cas"/>
</bean>
```

defaultRoles/ defaultPermissions：默认添加给所有 CAS 登录成功用户的角色和权限信息； roleAttributeNames/ permissionAttributeNames：角色属性 / 权限属性名称，如果用户的角色 / 权限信息是从服务器端返回的（即返回的 CAS Principal 中除了 Principal 之外还有如一些 Attributes），此时可以使用 roleAttributeNames/ permissionAttributeNames 得到 Attributes 中的角色 / 权限数据；请自行查询 CAS 获取用户更多信息。

```xml
<bean id="casFilter" class="org.apache.shiro.cas.CasFilter">
    <property name="failureUrl" value="/casFailure.jsp"/>
</bean>
```

CasFilter 类似于 FormAuthenticationFilter，只不过其验证服务器端返回的 CAS Service Ticket。

```xml
<bean id="shiroFilter" class="org.apache.shiro.spring.web.ShiroFilterFactoryBean">
    <property name="securityManager" ref="securityManager"/>
    <property name="loginUrl" value="https://localhost:8443/chapter14-server/login?service=https://localhost:9443/chapter14-client/cas"/>
    <property name="successUrl" value="/"/>
    <property name="filters">
        <util:map>
            <entry key="cas" value-ref="casFilter"/>
        </util:map>
    </property>
    <property name="filterChainDefinitions">
        <value>
            /casFailure.jsp = anon
            /cas = cas
            /logout = logout
            /** = user
        </value>
    </property>
</bean>
```

`loginUrl：https://localhost:8443/chapter15-server/login` 表示服务端端登录地址，登录成功后跳转到?service 参数对于的地址进行客户端验证及登录；
“/cas=cas”：即 /cas 地址是服务器端回调地址，使用 CasFilter 获取 Ticket 进行登录。

7、测试，输入 `http://localhost:9080/chapter15-client` 地址进行测试即可，可以使用如 Chrome 开这 debug 观察网络请求的变化。

如果遇到以下异常，一般是证书导入错误造成的，请尝试重新导入，如果还是不行，有可能是运行应用的 JDK 和安装数字证书的 JDK 不是同一个造成的：

```
Caused by:   sun.security.validator.ValidatorException: PKIX path building failed: sun.security.provider.certpath.SunCertPathBuilderException: unable to find valid certification path to requested target  

at sun.security.validator.PKIXValidator.doBuild(PKIXValidator.java:385)
at sun.security.validator.PKIXValidator.engineValidate(PKIXValidator.java:292)
at sun.security.validator.Validator.validate(Validator.java:260)
at sun.security.ssl.X509TrustManagerImpl.validate(X509TrustManagerImpl.java:326)
at sun.security.ssl.X509TrustManagerImpl.checkTrusted(X509TrustManagerImpl.java:231)
at sun.security.ssl.X509TrustManagerImpl.checkServerTrusted(X509TrustManagerImpl.java:126)
at sun.security.ssl.ClientHandshaker.serverCertificate(ClientHandshaker.java:1323)
   ... 67 more  

Caused by: sun.security.provider.certpath.SunCertPathBuilderException: unable to find valid certification path to requested target

at sun.security.provider.certpath.SunCertPathBuilder.engineBuild(SunCertPathBuilder.java:196)
at java.security.cert.CertPathBuilder.build(CertPathBuilder.java:268)
at sun.security.validator.PKIXValidator.doBuild(PKIXValidator.java:380)
... 73 more
```

# 14、Shiro 综合实例

2020-12-04 09:45 更新

## 综合实例

![img](https://atts.w3cschool.cn/attachments/image/wk/shiro/19.png)

## 简单数据字典

用户 (sys_user)

| 名称     | 类型    | 长度 | 描述         |
| -------- | ------- | ---- | ------------ |
| id       | bigint  |      | 编号 主键    |
| username | varchar | 100  | 用户名       |
| password | varchar | 100  | 密码         |
| salt     | varchar | 50   | 盐           |
| role_ids | varchar | 100  | 角色列表     |
| locked   | bool    |      | 账户是否锁定 |

组织机构 (sys_organization)

| 名称       | 类型    | 长度 | 描述       |
| ---------- | ------- | ---- | ---------- |
| id         | bigint  |      | 编号 主键  |
| name       | varchar | 100  | 组织机构名 |
| priority   | int     |      | 显示顺序   |
| parent_id  | bigint  |      | 父编号     |
| parent_ids | varchar | 100  | 父编号列表 |
| available  | bool    |      | 是否可用   |

资源 (sys_resource)

| 名称       | 类型    | 长度 | 描述       |
| ---------- | ------- | ---- | ---------- |
| id         | bigint  |      | 编号 主键  |
| name       | varchar | 100  | 资源名称   |
| type       | varchar | 50   | 资源类型， |
| priority   | int     |      | 显示顺序   |
| parent_id  | bigint  |      | 父编号     |
| parent_ids | varchar | 100  | 父编号列表 |
| permission | varchar | 100  | 权限字符串 |
| available  | bool    |      | 是否可用   |

角色 (sys_role)

| 名称         | 类型    | 长度 | 描述       |
| ------------ | ------- | ---- | ---------- |
| id           | bigint  |      | 编号 主键  |
| role         | varchar | 100  | 角色名称   |
| description  | varchar | 100  | 角色描述   |
| resource_ids | varchar | 100  | 授权的资源 |
| available    | bool    |      | 是否可用   |

**资源**：表示菜单元素、页面按钮元素等；菜单元素用来显示界面菜单的，页面按钮是每个页面可进行的操作，如新增、修改、删除按钮；使用 type 来区分元素类型（如 menu 表示菜单，button 代表按钮），priority 是元素的排序，如菜单显示顺序；permission 表示权限；如用户菜单使用 `user:*`；也就是把菜单授权给用户后，用户就拥有了 `user:*` 权限；如用户新增按钮使用 user:create，也就是把用户新增按钮授权给用户后，用户就拥有了 user:create 权限了；available 表示资源是否可用，如菜单显示 / 不显示。

**角色**：role 表示角色标识符，如 admin，用于后台判断使用；description 表示角色描述，如超级管理员，用于前端显示给用户使用；resource_ids 表示该角色拥有的资源列表，即该角色拥有的权限列表（显示角色），即角色是权限字符串集合；available 表示角色是否可用。

**组织机构**：name 表示组织机构名称，priority 是组织机构的排序，即显示顺序；available 表示组织机构是否可用。

**用户**：username 表示用户名；password 表示密码；salt 表示加密密码的盐；role_ids 表示用户拥有的角色列表，可以通过角色再获取其权限字符串列表；locked 表示用户是否锁定。

此处如资源、组织机构都是树型结构：

| id   | name       | parent_id | parent_ids |
| ---- | ---------- | --------- | ---------- |
| 1    | 总公司     | 0         | 0/         |
| 2    | 山东分公司 | 1         | 0/1/       |
| 3    | 河北分公司 | 1         | 0/1/       |
| 4    | 济南分公司 | 2         | 0/1/2/     |

parent_id 表示父编号，parent_ids 表示所有祖先编号；如 0/1/2/ 表示其祖先是 2、1、0；其中根节点父编号为 0。

为了简单性，如用户 - 角色，角色 - 资源关系直接在实体（用户表中的 role_ids，角色表中的 resource_ids）里完成的，没有建立多余的关系表，如要查询拥有 admin 角色的用户时，建议建立关联表，否则就没必要建立了。在存储关系时如 role_ids=1,2,3,；多个之间使用逗号分隔。

用户组、组织机构组本实例没有实现，即可以把一组权限授权给这些组，组中的用户 / 组织机构就自动拥有这些角色 / 权限了；另外对于用户组可以实现一个默认用户组，如论坛，不管匿名 / 登录用户都有查看帖子的权限。

更复杂的权限请参考我的《JavaEE 项目开发脚手架》：http://github.com/zhangkaitao/es。

## 表 / 数据 SQL

具体请参考

- sql/ shiro-schema.sql （表结构）
- sql/ shiro-data.sql （初始数据）

默认用户名 / 密码是 admin/123456。

## 实体

具体请参考 com.github.zhangkaitao.shiro.chapter16.entity 包下的实体，此处就不列举了。

## DAO

具体请参考 com.github.zhangkaitao.shiro.chapter16.dao 包下的 DAO 接口及实现。

## Service

具体请参考 com.github.zhangkaitao.shiro.chapter16.service 包下的 Service 接口及实现。以下是出了基本 CRUD 之外的关键接口：

```java
public interface ResourceService {
    Set<String> findPermissions(Set<Long> resourceIds); //得到资源对应的权限字符串
    List<Resource> findMenus(Set<String> permissions); //根据用户权限得到菜单
}
public interface RoleService {
    Set<String> findRoles(Long... roleIds); //根据角色编号得到角色标识符列表
    Set<String> findPermissions(Long[] roleIds); //根据角色编号得到权限字符串列表
}
public interface UserService {
    public void changePassword(Long userId, String newPassword); //修改密码
    public User findByUsername(String username); //根据用户名查找用户
    public Set<String> findRoles(String username);// 根据用户名查找其角色
    public Set<String> findPermissions(String username);// 根据用户名查找其权限
}
```

Service 实现请参考源代码，此处就不列举了。

## UserRealm 实现

```java
public class UserRealm extends AuthorizingRealm {
    @Autowired private UserService userService;
    protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principals) {
        String username = (String)principals.getPrimaryPrincipal();
        SimpleAuthorizationInfo authorizationInfo = new SimpleAuthorizationInfo();
        authorizationInfo.setRoles(userService.findRoles(username));
        authorizationInfo.setStringPermissions(userService.findPermissions(username));
        System.out.println(userService.findPermissions(username));
        return authorizationInfo;
    }
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
        String username = (String)token.getPrincipal();
        User user = userService.findByUsername(username);
        if(user == null) {
            throw new UnknownAccountException();//没找到帐号
        }
        if(Boolean.TRUE.equals(user.getLocked())) {
            throw new LockedAccountException(); //帐号锁定
        }
        return new SimpleAuthenticationInfo(
                user.getUsername(), //用户名
                user.getPassword(), //密码
                ByteSource.Util.bytes(user.getCredentialsSalt()),//salt=username+salt
                getName()  //realm name
        );
    }
}
```

此处的 UserRealm 和《第六章 Realm 及相关对象》中的 UserRealm 类似，通过 UserService 获取帐号及角色 / 权限信息。

## Web 层控制器

```java
@Controller
public class IndexController {
    @Autowired
    private ResourceService resourceService;
    @Autowired
    private UserService userService;
    @RequestMapping("/")
    public String index(@CurrentUser User loginUser, Model model) {
        Set<String> permissions = userService.findPermissions(loginUser.getUsername());
        List<Resource> menus = resourceService.findMenus(permissions);
        model.addAttribute("menus", menus);
        return "index";
    }
}
```

IndexController 中查询菜单在前台界面显示，请参考相应的 jsp 页面；

```java
@Controller
public class LoginController {
    @RequestMapping(value = "/login")
    public String showLoginForm(HttpServletRequest req, Model model) {
        String exceptionClassName = (String)req.getAttribute("shiroLoginFailure");
        String error = null;
        if(UnknownAccountException.class.getName().equals(exceptionClassName)) {
            error = "用户名/密码错误";
        } else if(IncorrectCredentialsException.class.getName().equals(exceptionClassName)) {
            error = "用户名/密码错误";
        } else if(exceptionClassName != null) {
            error = "其他错误：" + exceptionClassName;
        }
        model.addAttribute("error", error);
        return "login";
    }
}
```

LoginController 用于显示登录表单页面，其中 shiro authc 拦截器进行登录，登录失败的话会把错误存到 shiroLoginFailure 属性中，在该控制器中获取后来显示相应的错误信息。

```java
@RequiresPermissions("resource:view")
@RequestMapping(method = RequestMethod.GET)
public String list(Model model) {
    model.addAttribute("resourceList", resourceService.findAll());
    return "resource/list";
}
```

在控制器方法上使用 @RequiresPermissions 指定需要的权限信息，其他的都是类似的，请参考源码。

## Web 层标签库

com.github.zhangkaitao.shiro.chapter16.web.taglib.Functions 提供了函数标签实现，有根据编号显示资源 / 角色 / 组织机构名称，其定义放在 src/main/webapp/tld/zhang-functions.tld。

## Web 层异常处理器

```java
@ControllerAdvice
public class DefaultExceptionHandler {
    @ExceptionHandler({UnauthorizedException.class})
    @ResponseStatus(HttpStatus.UNAUTHORIZED)
    public ModelAndView processUnauthenticatedException(NativeWebRequest request, UnauthorizedException e) {
        ModelAndView mv = new ModelAndView();
        mv.addObject("exception", e);
        mv.setViewName("unauthorized");
        return mv;
    }
}
```

如果抛出 UnauthorizedException，将被该异常处理器截获来显示没有权限信息。

## Spring 配置——spring-config.xml

定义了 context:component-scan 来扫描除 web 层的组件、dataSource（数据源）、事务管理器及事务切面等；具体请参考配置源码。

## Spring 配置——spring-config-cache.xml

定义了 spring 通用 cache，使用 ehcache 实现；具体请参考配置源码。

## Spring 配置——spring-config-shiro.xml

定义了 shiro 相关组件。

```xml
<bean id="userRealm" class="com.github.zhangkaitao.shiro.chapter16.realm.UserRealm">
    <property name="credentialsMatcher" ref="credentialsMatcher"/>
    <property name="cachingEnabled" value="false"/>
</bean>
```

userRealm 组件禁用掉了 cache，可以参考 https://github.com/zhangkaitao/es/tree/master/web/src/main/java/com/sishuok/es/extra/aop 实现自己的 cache 切面；否则需要在修改如资源 / 角色等信息时清理掉缓存。

```xml
<bean id="sysUserFilter" 
class="com.github.zhangkaitao.shiro.chapter16.web.shiro.filter.SysUserFilter"/>
```

sysUserFilter 用于根据当前登录用户身份获取 User 信息放入 request；然后就可以通过 request 获取 User。

```xml
<property name="filterChainDefinitions">
  <value>
    /login = authc
    /logout = logout
    /authenticated = authc
    /** = user,sysUser
  </value>
</property>
```

如上是 shiroFilter 的 filterChainDefinitions 定义。

## Spring MVC 配置——spring-mvc.xml

定义了 spring mvc 相关组件。

```xml
<mvc:annotation-driven>
  <mvc:argument-resolvers>
    <bean class="com.github.zhangkaitao.shiro.chapter16
        .web.bind.method.CurrentUserMethodArgumentResolver"/>
  </mvc:argument-resolvers>
</mvc:annotation-driven>
```

此处注册了一个 @CurrentUser 参数解析器。如之前的 IndexController，从 request 获取 shiro sysUser 拦截器放入的当前登录 User 对象。

## Spring MVC 配置——spring-mvc-shiro.xml

定义了 spring mvc 相关组件。

```xml
<aop:config proxy-target-class="true"></aop:config>
<bean class="org.apache.shiro.spring.security
    .interceptor.AuthorizationAttributeSourceAdvisor">
  <property name="securityManager" ref="securityManager"/>
</bean>
```

定义 aop 切面，用于代理如 @RequiresPermissions 注解的控制器，进行权限控制。

## web.xml 配置文件

定义 Spring ROOT 上下文加载器、ShiroFilter、及 SpringMVC 拦截器。具体请参考源码。

## JSP 页面

```xml
<shiro:hasPermission name="user:create">
    <a href="${pageContext.request.contextPath}/user/create">用户新增</a><br/>
</shiro:hasPermission>
```

使用 shiro 标签进行权限控制。具体请参考源码。

## 系统截图

访问 http://localhost:8080/chapter16/；
首先进入登录页面，输入用户名 / 密码（默认 admin/123456）登录：

![image-20211116140608259](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211116140608259.png)

登录成功后到达整个页面主页，并根据当前用户权限显示相应的菜单，此处菜单比较简单，没有树型结构显示

![image-20211116140621899](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211116140621899.png)

然后就可以进行一些操作，如组织机构维护、用户修改、资源维护、角色授权

![image-20211116140638601](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211116140638601.png)

![image-20211116140646768](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211116140646768.png)

![image-20211116140657234](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211116140657234.png)

![image-20211116140709287](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211116140709287.png)



# 15、Shiro 拦截器机制

> 其中AccessControlFilter的方法很重要

## 拦截器机制

## 拦截器介绍

Shiro 使用了与 Servlet 一样的 Filter 接口进行扩展；所以如果对 Filter 不熟悉可以参考《Servlet 3.1 规范》http://www.iteye.com/blogs/subjects/Servlet-3-1了解 Filter 的工作原理。首先下图是 Shiro 拦截器的基础类图：

![image-20211119170032137](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211119170032137.png)

### **NameableFilter**

NameableFilter 给 Filter 起个名字，如果没有设置默认就是 FilterName；还记得之前的如 authc 吗？当我们组装拦截器链时会根据这个名字找到相应的拦截器实例；

比如我们的默认配置里面有过滤器**`FormAuthenticationFilter`**

```java
org.apache.shiro.web.filter.authc.FormAuthenticationFilter
```

在配置shiroFilter的时候，我们用**`authc`**来表示

我们自己定义的过滤器有

```java
	filters.put("jwt", jwtFilter);
	shiroFilter.setFilters(filters);
```

就是把我们定义的过滤器**`jwtFilter`**用**`jwt`**

### **OncePerRequestFilter**

​	OncePerRequestFilter 用于防止多次执行 Filter 的；也就是说一次请求只会走一次拦截器链；另外提供 enabled 属性，表示是否开启该拦截器实例，默认 enabled=true 表示开启，如果不想让某个拦截器工作，可以设置为 false 即可。

```java
public final void doFilter(ServletRequest request, ServletResponse response, FilterChain filterChain)
            throws ServletException, IOException {
        String alreadyFilteredAttributeName = getAlreadyFilteredAttributeName();//有则说明当前的过滤器已经进行过过滤
        if ( request.getAttribute(alreadyFilteredAttributeName) != null ) {
            log.trace("Filter '{}' already executed.  Proceeding without invoking this filter.", getName());
            filterChain.doFilter(request, response);  //交给下一个过滤器，或者执行我们的业务方法
        } else //noinspection deprecation
            if (/* added in 1.2: */ !isEnabled(request, response) ||
                /* retain backwards compatibility: */ shouldNotFilter(request) ) {
                //如果这个过滤器没有开启也交给下一个过滤器，或者执行我们的业务方法
            log.debug("Filter '{}' is not enabled for the current request.  Proceeding without invoking this filter.",
                    getName());
            filterChain.doFilter(request, response); 
        } else {
            log.trace("Filter '{}' not yet executed.  Executing now.", getName());
             //执行这个过滤器 
            request.setAttribute(alreadyFilteredAttributeName, Boolean.TRUE); 
            try {
             //我们自己来定义的抽象的方法
                doFilterInternal(request, response, filterChain);
            } finally {
                request.removeAttribute(alreadyFilteredAttributeName);
            }
        }
    }
```

在**OncePerRequestFilter**中有方法，来判断是否执行。
**执行的过滤器进行记录，没执行的执行后进行记录**

### **AdviceFilter**

AdviceFilter 提供了 AOP 风格的支持，类似于 SpringMVC 中的 Interceptor：

这个类重写**OncePerRequestFilter**类中的抽象方法

```java
 doFilterInternal(request, response, filterChain)
```

还添加的其他类如同

```java
boolean preHandle(ServletRequest request, ServletResponse response) throws Exception
void postHandle(ServletRequest request, ServletResponse response) throws Exception
void afterCompletion(ServletRequest request, ServletResponse response, Exception exception) throws Exception;
```

- **preHandler**：类似于 AOP 中的前置增强；在拦截器链执行之前执行；如果返回 true 则继续拦截器链；否则中断后续的拦截器链的执行直接返回；进行预处理（如基于表单的身份验证、授权）

- **postHandle**：类似于 AOP 中的后置返回增强；在拦截器链执行完成后执行；进行后处理（如记录执行时间之类的）；

- **afterCompletion**：类似于 AOP 中的后置最终增强；即不管有没有异常都会执行；可以进行清理资源（如解除 Subject 与线程的绑定之类的）；

  >  **AOP 即 filterChain.doFilter(request, response);** 

### **PathMatchingFilter**

PathMatchingFilter 提供了基于 Ant 风格的请求路径匹配功能及拦截器参数解析的功能。

在我们的**shiroConfig**里面我们设置有对应

```java
  @Bean
  public ShiroFilterChainDefinition shiroFilterChainDefinition() {
	DefaultShiroFilterChainDefinition chainDefinition = new DefaultShiroFilterChainDefinition();
	Map<String, String> filterMap = new LinkedHashMap<>();
	filterMap.put("/**", "jwt");
	chainDefinition.addPathDefinitions(filterMap);
	return chainDefinition;
  }
```

我们这里**`filterMap.put("/**", "jwt")`**就是我们的请求路径和对应的处理器关系，有方法

```java
boolean pathsMatch(String path, ServletRequest request)
boolean onPreHandle(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception
```

**pathsMatch**：该方法用于 path 与请求路径进行匹配的方法；如果匹配返回 true；
**onPreHandle**：在 preHandle 中，当 pathsMatch 匹配一个路径后，会调用 opPreHandler 方法并将路径绑定参数配置传给 mappedValue；然后可以在这个方法中进行一些验证（如角色授权），如果验证失败可以返回 false 中断流程；默认返回 true；**也就是说子类可以只实现 onPreHandle 即可，无须实现 preHandle。如果没有 path 与请求路径匹配，默认是通过的（即 preHandle 返回 true）。**

### **AccessControlFilter**

如果用户没有认证（即登录)，那么这个过滤器就是控制访问资源和用户重定向到登录页面的过滤器的父类。他还重写了对应的 **onPreHandle**方法

```java
    public boolean onPreHandle(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
        return isAccessAllowed(request, response, mappedValue) || onAccessDenied(request, response, mappedValue);
    }
```

AccessControlFilter 提供了访问控制的基础功能；比如是否允许访问/当访问拒绝时如何处理等：

```java
abstract boolean isAccessAllowed(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception;
boolean onAccessDenied(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception;
abstract boolean onAccessDenied(ServletRequest request, ServletResponse response) throws Exception;
```

**isAccessAllowed**：表示是否允许访问；mappedValue 就是[urls]配置中拦截器参数部分，如果允许访问返回 true，否则 false；

**onAccessDenied**：表示当访问拒绝时是否已经处理了；如果返回 true 表示需要继续处理；如果返回 false 表示该拦截器实例已经处理了，将直接返回即可。

onPreHandle 会自动调用这两个方法决定是否继续处理：

```java
boolean onPreHandle(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
    return isAccessAllowed(request, response, mappedValue) || onAccessDenied(request, response, mappedValue);
}
```

另外 AccessControlFilter 还提供了如下方法用于处理如登录成功后/重定向到上一个请求：

```java
void setLoginUrl(String loginUrl) //身份验证时使用，默认/login.jsp
String getLoginUrl()
Subject getSubject(ServletRequest request, ServletResponse response) //获取Subject 实例
boolean isLoginRequest(ServletRequest request, ServletResponse response)//当前请求是否是登录请求
void saveRequestAndRedirectToLogin(ServletRequest request, ServletResponse response) throws IOException //将当前请求保存起来并重定向到登录页面
void saveRequest(ServletRequest request) //将请求保存起来，如登录成功后再重定向回该请求
void redirectToLogin(ServletRequest request, ServletResponse response) //重定向到登录页面&nbsp;
```

比如基于表单的身份验证就需要使用这些功能。

到此基本的拦截器就完事了，如果我们想进行访问访问的控制就可以继承 AccessControlFilter；如果我们要添加一些通用数据我们可以直接继承 PathMatchingFilter。

### AuthenticationFilter

在**AuthenticationFilter**中实现了抽象方法

```java
    @Override    
	protected boolean isAccessAllowed(ServletRequest request, ServletResponse response, Object mappedValue) {
        Subject subject = getSubject(request, response);
        return subject.isAuthenticated() && subject.getPrincipal() != null;
    }
```

> **即判断是否已经认证过以及主体标识符不能为空**

### AuthenticatingFilter

在**AuthenticatingFilter**中实现了抽象方法

```java
    @Override
    protected boolean isAccessAllowed(ServletRequest request, ServletResponse response, Object mappedValue) {
        return super.isAccessAllowed(request, response, mappedValue) ||
                (!isLoginRequest(request, response) && isPermissive(mappedValue));
    }
```

> **非登入请求而且是允许访问的路径。**
>
> 1、super.isAccessAllowed(request, response, mappedValue)为**A**
> 2、(!isLoginRequest(request, response) && isPermissive(mappedValue))为**B1和B2** **(必定是false的)**
>
> 但是因为isLoginRequest(request, response)中的判断一直以login.jsp为判定的即一直是**true**，而isPermissive(mappedValue)一直是**false**
>
> **情况一：需要登入状态下才能执行的接口**
>
> 比如我们的edit编辑，在**无登入状态下**（A返回false），则**isAccessAllowed**返回一个**false**，然后判断我们的被拒绝访问的情况
>
> **情况二：登入接口**
>
> 是在**无登入状态下**（A返回false），则**isAccessAllowed**又返回一个**false**，然后判断我们的被拒绝访问的情况
>
> **情况三：其他接口**
>
> 1、是在**无登入状态下**（A返回false），则**isAccessAllowed**又返回一个**false**，即我们可以被拒绝访问接口。
> 2、是在**登入状态下**（A返回true），则**isAccessAllowed**又返回一个**true**，即我们可以直接继续访问接口。

综上我们几乎被调用到我们的**`onAccessDenied`**

```java
  @Override
  protected boolean onAccessDenied(ServletRequest servletRequest, ServletResponse servletResponse) throws Exception {
	HttpServletRequest request = (HttpServletRequest) servletRequest;
	String jwt = request.getHeader("Authorization");
	if (ObjectUtils.isEmpty(jwt)) {
	  return true;
	} else {
	  //校验jwt
	  Claims claimByToken = jwtUtils.getClaimByToken(jwt);
	  if (claimByToken == null || jwtUtils.isTokenExpired(claimByToken.getExpiration())) {
	    //第一次登入或者token失效
		throw new ExpiredCredentialsException("token已经失效，请重新登录");
	  }
	  //执行登入
	  return executeLogin(servletRequest, servletResponse);
	}
  }
```

![image-20211120012824550](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211120012824550.png)

执行登入里面才有对应的**subject.login(token)**去进行身份的验证

```java
protected boolean executeLogin(ServletRequest request, ServletResponse response) throws Exception {
    AuthenticationToken token = createToken(request, response);
    if (token == null) {
        String msg = "createToken method implementation returned null. A valid non-null AuthenticationToken " +
                "must be created in order to execute a login attempt.";
        throw new IllegalStateException(msg);
    }
    try {
        Subject subject = getSubject(request, response);
        subject.login(token);
        return onLoginSuccess(token, subject, request, response);
    } catch (AuthenticationException e) {
        return onLoginFailure(token, e, request, response);
    }
}
```

## 拦截器链

Shiro 对 Servlet 容器的 FilterChain 进行了代理，即 ShiroFilter 在继续 Servlet 容器的 Filter 链的执行之前，通过 ProxiedFilterChain 对 Servlet 容器的 FilterChain 进行了代理；即先走 Shiro 自己的 Filter 体系，然后才会委托给 Servlet 容器的 FilterChain 进行 Servlet 容器级别的 Filter 链执行；Shiro 的 ProxiedFilterChain 执行流程：1、先执行 Shiro 自己的 Filter 链；2、再执行 Servlet 容器的 Filter 链（即原始的 Filter）。

而 ProxiedFilterChain 是通过 FilterChainResolver 根据配置文件中[urls]部分是否与请求的 URL 是否匹配解析得到的。

```java
FilterChain getChain(ServletRequest request, ServletResponse response, FilterChain originalChain);
```

即传入原始的 chain 得到一个代理的 chain。

Shiro 内部提供了一个路径匹配的 FilterChainResolver 实现：PathMatchingFilterChainResolver，其根据[urls]中配置的 url 模式（默认 Ant 风格）=拦截器链和请求的 url 是否匹配来解析得到配置的拦截器链的；而 PathMatchingFilterChainResolver 内部通过 FilterChainManager 维护着拦截器链，比如 DefaultFilterChainManager 实现维护着 url 模式与拦截器链的关系。因此我们可以通过 FilterChainManager 进行动态动态增加 url 模式与拦截器链的关系。

DefaultFilterChainManager 会默认添加 org.apache.shiro.web.filter.mgt.DefaultFilter 中声明的拦截器：

```java
public enum DefaultFilter {
    anon(AnonymousFilter.class),
    authc(FormAuthenticationFilter.class),
    authcBasic(BasicHttpAuthenticationFilter.class),
    logout(LogoutFilter.class),
    noSessionCreation(NoSessionCreationFilter.class),
    perms(PermissionsAuthorizationFilter.class),
    port(PortFilter.class),
    rest(HttpMethodPermissionFilter.class),
    roles(RolesAuthorizationFilter.class),
    ssl(SslFilter.class),
    user(UserFilter.class);
}
```

下一节会介绍这些拦截器的作用。

如果要注册自定义拦截器，IniSecurityManagerFactory/WebIniSecurityManagerFactory 在启动时会自动扫描 ini 配置文件中的 [filters]/[main] 部分并注册这些拦截器到 DefaultFilterChainManager；且创建相应的 url 模式与其拦截器关系链。如果使用 Spring 后续章节会介绍如果注册自定义拦截器。

如果想自定义 FilterChainResolver，可以通过实现 WebEnvironment 接口完成：

```java
public class MyIniWebEnvironment extends IniWebEnvironment {
    @Override
    protected FilterChainResolver createFilterChainResolver() {
        //在此处扩展自己的FilterChainResolver
        return super.createFilterChainResolver();
    }
}
```

FilterChain 之间的关系。如果想动态实现 url -拦截器的注册，就可以通过实现此处的 FilterChainResolver 来完成，比如：

```java
//1、创建 FilterChainResolver
PathMatchingFilterChainResolver filterChainResolver =
        new PathMatchingFilterChainResolver();
//2、创建 FilterChainManager
DefaultFilterChainManager filterChainManager = new DefaultFilterChainManager();
//3、注册 Filter
for(DefaultFilter filter : DefaultFilter.values()) {
    filterChainManager.addFilter(
        filter.name(), (Filter) ClassUtils.newInstance(filter.getFilterClass()));
}
//4、注册 URL-Filter 的映射关系
filterChainManager.addToChain("/login.jsp", "authc");
filterChainManager.addToChain("/unauthorized.jsp", "anon");
filterChainManager.addToChain("/**", "authc");
filterChainManager.addToChain("/**", "roles", "admin");
//5、设置 Filter 的属性
FormAuthenticationFilter authcFilter =
         (FormAuthenticationFilter)filterChainManager.getFilter("authc");
authcFilter.setLoginUrl("/login.jsp");
RolesAuthorizationFilter rolesFilter =
          (RolesAuthorizationFilter)filterChainManager.getFilter("roles");
rolesFilter.setUnauthorizedUrl("/unauthorized.jsp");
filterChainResolver.setFilterChainManager(filterChainManager);
return filterChainResolver;
```

此处自己去实现注册 filter，及url 模式与 filter 之间的映射关系。可以通过定制 FilterChainResolver 或 FilterChainManager 来完成诸如动态 URL 匹配的实现。

然后再 web.xml 中进行如下配置 Environment：

```xml
<context-param>
<param-name>shiroEnvironmentClass</param-name> <param-value>com.github.zhangkaitao.shiro.chapter8.web.env.MyIniWebEnvironment</param-value>
</context-param>
```

## 自定义拦截器

通过自定义自己的拦截器可以扩展一些功能，诸如动态 url -角色/权限访问控制的实现、根据 Subject 身份信息获取用户信息绑定到 Request（即设置通用数据）、验证码验证、在线用户信息的保存等等，因为其本质就是一个 Filter；所以 Filter 能做的它就能做。

对于 Filter 的介绍请参考《Servlet规范》中的 Filter 部分：
http://www.iteye.com/blogs/subjects/Servlet-3-1。

**1、扩展 OncePerRequestFilter**

OncePerRequestFilter 保证一次请求只调用一次 doFilterInternal，即如内部的 forward 不会再多执行一次 doFilterInternal：

```java
public class MyOncePerRequestFilter extends OncePerRequestFilter {
    @Override
    protected void doFilterInternal(ServletRequest request, ServletResponse response, FilterChain chain) throws ServletException, IOException {
        System.out.println("=========once per request filter");
        chain.doFilter(request, response);
    }
}
```

然后再 shiro.ini 配置文件中：

```ini
[main]
myFilter1=com.github.zhangkaitao.shiro.chapter8.web.filter.MyOncePerRequestFilter
\#[filters]
\#myFilter1=com.github.zhangkaitao.shiro.chapter8.web.filter.MyOncePerRequestFilter
[urls]
/**=myFilter1
```

Filter 可以在 [main] 或 [filters] 部分注册，然后在 [urls] 部分配置 url 与 filter 的映射关系即可。

**2、扩展 AdviceFilter**

AdviceFilter 提供了 AOP 的功能，其实现和 SpringMVC 中的 Interceptor 思想一样：具体可参考我的 SpringMVC 教程中的处理器拦截器部分：
http://www.iteye.com/blogs/subjects/kaitao-springmvc

```java
public class MyAdviceFilter extends AdviceFilter {
    @Override
    protected boolean preHandle(ServletRequest request, ServletResponse response) throws Exception {
        System.out.println("====预处理/前置处理");
        return true;//返回 false 将中断后续拦截器链的执行
    }
    @Override
    protected void postHandle(ServletRequest request, ServletResponse response) throws Exception {
        System.out.println("====后处理/后置返回处理");
    }
    @Override
    public void afterCompletion(ServletRequest request, ServletResponse response, Exception exception) throws Exception {
        System.out.println("====完成处理/后置最终处理");
    }
}
```

- preHandle：进行请求的预处理，然后根据返回值决定是否继续处理（true：继续过滤器链）；可以通过它实现权限控制；
- postHandle：执行完拦截器链之后正常返回后执行；
- afterCompletion：不管最后有没有异常，afterCompletion 都会执行，完成如清理资源功能。

然后在 shiro.ini 中进行如下配置：

```ini
[filters]
myFilter1=com.github.zhangkaitao.shiro.chapter8.web.filter.MyOncePerRequestFilter
myFilter2=com.github.zhangkaitao.shiro.chapter8.web.filter.MyAdviceFilter
[urls]
/**=myFilter1,myFilter2
```

该过滤器的具体使用可参考我的 SpringMVC 教程中的处理器拦截器部分。

**3、PathMatchingFilter**

PathMatchingFilter 继承了 AdviceFilter，提供了 url 模式过滤的功能，如果需要对指定的请求进行处理，可以扩展 PathMatchingFilter：

```java
public class MyPathMatchingFilter extends PathMatchingFilter {
    @Override
    protected boolean onPreHandle(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
       System.out.println("url matches,config is " + Arrays.toString((String[])mappedValue));
       return true;
    }
}
```

- preHandle：会进行 url 模式与请求 url 进行匹配，如果匹配会调用 onPreHandle；如果没有配置 url 模式 / 没有 url 模式匹配，默认直接返回 true；
- onPreHandle：如果 url 模式与请求 url 匹配，那么会执行 onPreHandle，并把该拦截器配置的参数传入。默认什么不处理直接返回 true。

然后在 shiro.ini 中进行如下配置：

```ini
[filters]
myFilter3=com.github.zhangkaitao.shiro.chapter8.web.filter.MyPathMatchingFilter
[urls]
/**= myFilter3[config]
```

`/**` 就是注册给 PathMatchingFilter 的 url 模式，config 就是拦截器的配置参数，多个之间逗号分隔，onPreHandle 使用 mappedValue 接收参数值。

**4、扩展 AccessControlFilter**

AccessControlFilter 继承了 PathMatchingFilter，并扩展了了两个方法：

```java
public boolean onPreHandle(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
    return isAccessAllowed(request, response, mappedValue)
     || onAccessDenied(request, response, mappedValue);
}
```

isAccessAllowed：即是否允许访问，返回 true 表示允许；
onAccessDenied：表示访问拒绝时是否自己处理，如果返回 true 表示自己不处理且继续拦截器链执行，返回 false 表示自己已经处理了（比如重定向到另一个页面）。

```java
public class MyAccessControlFilter extends AccessControlFilter {
    protected boolean isAccessAllowed(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
        System.out.println("access allowed");
        return true;
    }
    protected boolean onAccessDenied(ServletRequest request, ServletResponse response) throws Exception {
        System.out.println("访问拒绝也不自己处理，继续拦截器链的执行");
        return true;
    }
}
```

然后在 shiro.ini 中进行如下配置：

**5、基于表单登录拦截器**

之前我们已经使用过 Shiro 内置的基于表单登录的拦截器了，此处自己做一个类似的基于表单登录的拦截器。

```java
public class FormLoginFilter extends PathMatchingFilter {
    private String loginUrl = "/login.jsp";
    private String successUrl = "/";
    @Override
    protected boolean onPreHandle(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
        if(SecurityUtils.getSubject().isAuthenticated()) {
            return true;//已经登录过
        }
        HttpServletRequest req = (HttpServletRequest) request;
        HttpServletResponse resp = (HttpServletResponse) response;
        if(isLoginRequest(req)) {
            if("post".equalsIgnoreCase(req.getMethod())) {//form表单提交
                boolean loginSuccess = login(req); //登录
                if(loginSuccess) {
                    return redirectToSuccessUrl(req, resp);
                }
            }
            return true;//继续过滤器链
        } else {//保存当前地址并重定向到登录界面
            saveRequestAndRedirectToLogin(req, resp);
            return false;
        }
    }
    private boolean redirectToSuccessUrl(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        WebUtils.redirectToSavedRequest(req, resp, successUrl);
        return false;
    }
    private void saveRequestAndRedirectToLogin(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        WebUtils.saveRequest(req);
        WebUtils.issueRedirect(req, resp, loginUrl);
    }
    private boolean login(HttpServletRequest req) {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        try {
            SecurityUtils.getSubject().login(new UsernamePasswordToken(username, password));
        } catch (Exception e) {
            req.setAttribute("shiroLoginFailure", e.getClass());
            return false;
        }
        return true;
    }
    private boolean isLoginRequest(HttpServletRequest req) {
        return pathsMatch(loginUrl, WebUtils.getPathWithinApplication(req));
    }
}
```

onPreHandle 主要流程：

1. 首先判断是否已经登录过了，如果已经登录过了继续拦截器链即可；
2. 如果没有登录，看看是否是登录请求，如果是 get 方法的登录页面请求，则继续拦截器链（到请求页面），否则如果是 get 方法的其他页面请求则保存当前请求并重定向到登录页面；
3. 如果是 post 方法的登录页面表单提交请求，则收集用户名 / 密码登录即可，如果失败了保存错误消息到 “shiroLoginFailure” 并返回到登录页面；
4. 如果登录成功了，且之前有保存的请求，则重定向到之前的这个请求，否则到默认的成功页面。

shiro.ini 配置

```
[filters]
formLogin=com.github.zhangkaitao.shiro.chapter8.web.filter.FormLoginFilter
[urls]
/test.jsp=formLogin
/login.jsp=formLogin
```

启动服务器输入 `http://localhost:8080/chapter8/test.jsp` 测试时，会自动跳转到登录页面，登录成功后又会跳回到 test.jsp 页面。

此处可以通过继承 AuthenticatingFilter 实现，其提供了很多登录相关的基础代码。另外可以参考 Shiro 内嵌的 FormAuthenticationFilter 的源码，思路是一样的。

**6、任意角色授权拦截器**

Shiro 提供 roles 拦截器，其验证用户拥有所有角色，没有提供验证用户拥有任意角色的拦截器。

```
public class AnyRolesFilter extends AccessControlFilter {
    private String unauthorizedUrl = "/unauthorized.jsp";
    private String loginUrl = "/login.jsp";
    protected boolean isAccessAllowed(ServletRequest request, ServletResponse response, Object mappedValue) throws Exception {
        String[] roles = (String[])mappedValue;
        if(roles == null) {
            return true;//如果没有设置角色参数，默认成功
        }
        for(String role : roles) {
            if(getSubject(request, response).hasRole(role)) {
                return true;
            }
        }
        return false;//跳到onAccessDenied处理
    }
    @Override
    protected boolean onAccessDenied(ServletRequest request, ServletResponse response) throws Exception {
        Subject subject = getSubject(request, response);
        if (subject.getPrincipal() == null) {//表示没有登录，重定向到登录页面
            saveRequest(request);
            WebUtils.issueRedirect(request, response, loginUrl);
        } else {
            if (StringUtils.hasText(unauthorizedUrl)) {//如果有未授权页面跳转过去
                WebUtils.issueRedirect(request, response, unauthorizedUrl);
            } else {//否则返回401未授权状态码
                WebUtils.toHttp(response).sendError(HttpServletResponse.SC_UNAUTHORIZED);
            }
        }
        return false;
    }
} 
```

流程：

1. 首先判断用户有没有任意角色，如果没有返回 false，将到 onAccessDenied 进行处理；
2. 如果用户没有角色，接着判断用户有没有登录，如果没有登录先重定向到登录；
3. 如果用户没有角色且设置了未授权页面（unauthorizedUrl），那么重定向到未授权页面；否则直接返回 401 未授权错误码。

shiro.ini 配置

```
[filters]
anyRoles=com.github.zhangkaitao.shiro.chapter8.web.filter.AnyRolesFilter
[urls]
/test.jsp=formLogin,anyRoles[admin,user]
/login.jsp=formLogin
```

此处可以继承 AuthorizationFilter 实现，其提供了授权相关的基础代码。另外可以参考 Shiro 内嵌的 RolesAuthorizationFilter 的源码，只是实现 hasAllRoles 逻辑。

## 默认拦截器

Shiro 内置了很多默认的拦截器，比如身份验证、授权等相关的。默认拦截器可以参考 org.apache.shiro.web.filter.mgt.DefaultFilter 中的枚举拦截器：

| 默认拦截器名      | 拦截器类                                                     | 说明（括号里的表示默认值）                                   |
| ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 身份验证相关的    |                                                              |                                                              |
| authc             | org.apache.shiro.web.filter.authc.FormAuthenticationFilter   | 基于表单的拦截器；如 “`/**=authc`”，如果没有登录会跳到相应的登录页面登录；主要属性：usernameParam：表单提交的用户名参数名（ username）；  passwordParam：表单提交的密码参数名（password）； rememberMeParam：表单提交的密码参数名（rememberMe）； loginUrl：登录页面地址（/login.jsp）；successUrl：登录成功后的默认重定向地址； failureKeyAttribute：登录失败后错误信息存储 key（shiroLoginFailure）； |
| authcBasic        | org.apache.shiro.web.filter.authc.BasicHttpAuthenticationFilter | Basic HTTP 身份验证拦截器，主要属性： applicationName：弹出登录框显示的信息（application）； |
| logout            | org.apache.shiro.web.filter.authc.LogoutFilter               | 退出拦截器，主要属性：redirectUrl：退出成功后重定向的地址（/）; 示例 “/logout=logout” |
| user              | org.apache.shiro.web.filter.authc.UserFilter                 | 用户拦截器，用户已经身份验证 / 记住我登录的都可；示例 “/**=user” |
| anon              | org.apache.shiro.web.filter.authc.AnonymousFilter            | 匿名拦截器，即不需要登录即可访问；一般用于静态资源过滤；示例 “/static/**=anon” |
| **授权相关的**    |                                                              |                                                              |
| roles             | org.apache.shiro.web.filter.authz.RolesAuthorizationFilter   | 角色授权拦截器，验证用户是否拥有所有角色；主要属性： loginUrl：登录页面地址（/login.jsp）；unauthorizedUrl：未授权后重定向的地址；示例 “/admin/**=roles[admin]” |
| perms             | org.apache.shiro.web.filter.authz.PermissionsAuthorizationFilter | 权限授权拦截器，验证用户是否拥有所有权限；属性和 roles 一样；示例 “/user/**=perms["user:create"]” |
| port              | org.apache.shiro.web.filter.authz.PortFilter                 | 端口拦截器，主要属性：port（80）：可以通过的端口；示例 “/test= port[80]”，如果用户访问该页面是非 80，将自动将请求端口改为 80 并重定向到该 80 端口，其他路径 / 参数等都一样 |
| rest              | org.apache.shiro.web.filter.authz.HttpMethodPermissionFilter | rest 风格拦截器，自动根据请求方法构建权限字符串（GET=read, POST=create,PUT=update,DELETE=delete,HEAD=read,TRACE=read,OPTIONS=read, MKCOL=create）构建权限字符串；示例 “/users=rest[user]”，会自动拼出“user:read,user:create,user:update,user:delete” 权限字符串进行权限匹配（所有都得匹配，isPermittedAll）； |
| ssl               | org.apache.shiro.web.filter.authz.SslFilter                  | SSL 拦截器，只有请求协议是 https 才能通过；否则自动跳转会 https 端口（443）；其他和 port 拦截器一样； |
| **其他**          |                                                              |                                                              |
| noSessionCreation | org.apache.shiro.web.filter.session.NoSessionCreationFilter  | 不创建会话拦截器，调用 subject.getSession(false) 不会有什么问题，但是如果 subject.getSession(true) 将抛出 DisabledSessionException 异常； |

另外还提供了一个 org.apache.shiro.web.filter.authz.HostFilter，即主机拦截器，比如其提供了属性：authorizedIps：已授权的 ip 地址，deniedIps：表示拒绝的 ip 地址；不过目前还没有完全实现，不可用。

这些默认的拦截器会自动注册，可以直接在 ini 配置文件中通过 “拦截器名. 属性” 设置其属性：

```
perms.unauthorizedUrl=/unauthorized
```

另外如果某个拦截器不想使用了可以直接通过如下配置直接禁用：

```
perms.enabled=false
```

示例源代码：[https://github.com/zhangkaitao/shiro-example]()

# 15、shiro整合springboot

如果要整合对应的shrio，我们需要一个Filter来在每一次拦截我们的请求并给每一个请求进行对应的认证和授权。

![image-20211117123323509](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211117123323509.png)

## 引入shiro

```xml
<dependency>
	<groupId>org.apache.shrio</groupId>
    <artifactId>shiro-spring-boot-starter</artifactId>
</dependency>
```

## 设置shrio.config

我们推荐创建两个文件夹

> Config文件夹：用来存放不同的整合框架的配置
> Shrio文件夹：来存放关于Shrio框架的代码
> Realms文件夹：专门来放置Realm的文件夹

```java
/**
 * 用来整合Shrio框架的相关配置
 */
@Configuration
public class ShrioConfig {
  @Bean
  public ShiroFilterFactoryBean getShiroFilterFactoryBean(DefaultWebSecurityManager defaultWebSecurityManager) {
	ShiroFilterFactoryBean shiroFilterFactoryBean = new ShiroFilterFactoryBean();
	shiroFilterFactoryBean.setSecurityManager(defaultWebSecurityManager);
	Map<String, String> map = new HashMap<>();
	//authc即该资源要认证和授权,是过滤器的一种
	map.put("/**","authc");
	//设置一个map看哪些资源是受限或者公共的
	shiroFilterFactoryBean.setFilterChainDefinitionMap(map);
	return shiroFilterFactoryBean;

  }
  /**
   * 2、创建安全管理器
   */
  @Bean
  public DefaultWebSecurityManager getDefaultWebSecurityManager(Realm realm) {
	DefaultWebSecurityManager defaultWebSecurityManager = new DefaultWebSecurityManager();
	defaultWebSecurityManager.setRealm(realm);
	return defaultWebSecurityManager;
  }
  /**
   * 3、创建自定义的realm
   */
  @Bean
  public Realm getRealm() {
	AccountRealm accountRealm = new AccountRealm();
	return accountRealm;
  }
}
```

