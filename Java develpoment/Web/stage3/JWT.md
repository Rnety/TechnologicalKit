# JWT

## 1、什么是JWT

JSON Web Token (JWT) is an open standard ([RFC 7519](https://tools.ietf.org/html/rfc7519)) that defines a compact and self-contained way for securely transmitting information between parties as a JSON object. This information can be verified and trusted because it is digitally signed. JWTs can be signed using a secret (with the **HMAC** algorithm) or a public/private key pair using **RSA** or **ECDSA**.

Although JWTs can be encrypted to also provide secrecy between parties, we will focus on *signed* tokens. Signed tokens can verify the *integrity* of the claims contained within it, while encrypted tokens *hide* those claims from other parties. When tokens are signed using public/private key pairs, the signature also certifies that only the party holding the private key is the one that signed it.

> JWT简称JSON Web Token,也就是通过JSON形式作为Web应用中的令牌,用于在各方之间安全地将信息作为JSON对象传输。在数据传输过程中还可以完成数据加密、签名等相关处理。

## 2、什么时候使用我们的JWT

Here are some scenarios where JSON Web Tokens are useful:

- **Authorization**: This is the most common scenario for using JWT. Once the user is logged in, each subsequent request will include the JWT, allowing the user to access routes, services, and resources that are permitted with that token. Single Sign On is a feature that widely uses JWT nowadays, because of its small overhead and its ability to be easily used across different domains.
- **Information Exchange**: JSON Web Tokens are a good way of securely transmitting information between parties. Because JWTs can be signed—for example, using public/private key pairs—you can be sure the senders are who they say they are. Additionally, as the signature is calculated using the header and the payload, you can also verify that the content hasn't been tampered with.

> - **授权**： 这是使用 JWT 最常见的方案。登录后，每个后续请求都将包括 JWT，允许用户访问该令牌允许的路线、服务和资源。单签名是当今广泛使用的 JWT 功能，因为它的开销很小，并且能够轻松地跨不同域使用。
> - **信息交换**：JSON网络代币是各方安全传递信息的好方法。例如，因为 JWT 可以签名，因此使用公共/私人密钥对，您可以确定发送者就是他们所说的他们是谁。此外，由于签名是使用头和有效载荷计算的，您还可以验证内容是否未被篡改。

## 3、为什么使用我们的JWT

### 3.1、基于传统的Session认证

我们知道，http协议本身是一种无状态的协议，而这就意味着如果用户向我们的应用提供了用户名和密码来进行用户认证，那么下一次请求时，用户还要再一次进行用户认证才行，因为根据http协议，我们并不能知道是哪个用户发出的请求，所以为了让我们的应用能识别是哪个用户发出的请求，我们只能在服务器存储一份用户登录的信息，这份登录信息会在响应时传递给浏览器，告诉其保存为cookie ,以便下次请求时发送给我们的应用，这样我们的应用就能识别请求来自哪个用户了,这就是传统的基于session认证。

### 3.2、认证流程

![image-20211112141440552](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211112141440552.png)

> **用户登入：**
>
> 1、当我们的用户进行第一次登入的时候，服务器在构建、建立了一个`Session`（服务器上面的一个对象）,当登入了成功的时候我们把我们的
>
> 用户的信息保存到我们的`Session`的里面
>
> 2、同时在第一次响应的时候以`Sessionid`以`cookie`的形式给客户端
>
> 3、以后访问的时候根据我们携带的`Sessionid`去服务端查看是否有对应的`cookie`
>
> 4、有则可以申请，没有则叫用户去认证

```java
@GetMapper("/test")
public String test(String username,HttpServletRequest request){
    request.getSession.setAttribute("username",username);
}
```

![image-20211112143047200](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211112143047200.png)

响应以后就给我们一个`cookie`里面有`Sessionid`之后每次请求都携带这个`cookie`

### 3.3、暴露的问题

1. 每个用户经过我们的应用认证之后，我们的应用都要在服务端做一次记录，以方便用户下次请求的鉴别，通常而言`session`都是保存在存中，而随着认证用户的增多，服务端的开销会明显增大

2. 用户认证之后，服务端做认证记录，如果认证的记录被保存在内存中的话，这意味着用户下次请求还必须要请求在这台服务器上，这样才拿到授权的资源，这样在分布式的应用上，相应的限制了负载均衡器的能力。这也意味着限制了应用的扩展能力。

3. 因为是基于`cookie`来进行用户识别的,`cookie`如果被截获，用户就会很容易受到跨站请求伪造的攻击。

4. 在前后端分离系统中就更加痛苦:如下图所示也就是说前后端分离在应用解耦后增加了部署的复杂性。通常用户一次请求就要转发多次。如果用`session` 每次携带`Sessionid`到服务器，服务器还要查询用户信息。同时如果用户很多。这些信息存储在服务器内存中，给服务器增加负担。还有就是CSRF(跨站伪造请求攻击)攻击，`session`是基于`cookie`进行用户识别的，`cookie`如果被截获，用户就会很容易受到跨站请求伪造的攻击。还有就是`sessionid`就是一个特征值，表达的信息不够丰富。不容易扩展。而且如果你后端应用是多节点部署。那么就需要实现`session`共享机制。不方便集群应用。

## 4、基于JWT认证

![image-20211112144548676](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211112144548676.png)

### 1、认证流程

1. 首先，前端通过Web表单将自己的用户名和密码发送到后端的接口。这一过程一般是一个HTTP POST请求。建议的方式是通过SSL加密的传输(https协议，从而避免敏感信息被嗅探。

2. 后端核对用户名和密码成功后，将用户的id等其他信息作为JWT Payload(负载)，将其与头部分别进行Base64编码拼接后签名形成一个JWT。形成的JWT就是一个形同111.zzz.xxx的字符串。

   > token `head.payload.singurater`

3. 后端将JWT字符串作为登录成功的返回结果返回给前端。前端可以将返回的结果保存在`localStorage`或`sessionStorage`上，**退出登录时前端删除保存的JWT即可。**

4. 前端在每次请求时将JWT放入HTTP Header中的Authorization位。(解决XSS和XSRF问题)。

5. 后端检查是否存在，如存在验证JWT的有效性。例如，检查签名是否正确;检查Token是否过期;检查Token的接收方是否是自己(可选)。

6. 验证通过后后端使用JWT中包含的用户信息进行其他逻辑操作，返回相应结果。

### 2、JWT优势

1. 简洁(Compact):可以通过URL，POST参数或者在HTTP header发送，因为数据量小，传输速度也很快
2. 自包含(Self-contained):负载中包含了所有用户所需要的信息，避免了多次查询数据库

> 比如我们的Session里面只存储了用户id，想要更多信息的还要查询数据库

3. 因为Token是以JSON加密的形式保存在客户端的，所以JWT是跨语言的，原则上任何web形式都支持。

4. 不需要在服务端保存会话信息，特别适用于分布式微服务。

## 5、JWT结构

token其实就是字符串，分为三个部分

- Header
- Payload
- Signature

Therefore, a JWT typically looks like the following.

```
xxxxx.yyyyy.zzzzz
```

### 5.1、Header

头部分由两个部分组成：令牌的类型（即 JWT）和正在使用的签名算法，如 HMAC SHA256 或 RSA。

例如：

```json
{
  "alg": "HS256", //推荐使用算法
  "typ": "JWT"	  //类型
}
```

然后，此 JSON 是**Base64Url**编码，以形成 JWT 的第一部分。

注意：Base64是一种编码，也就是说，它是可以被翻译回原来的样子来的。它并不是一种加密过程。

### 5.2、Payload

令牌的第二部分是有效负载，其中包含声明。声明是有关实体（通常是用户）和其他数据的声明。

同样的，它会使用**Base64Url**编码组成JWT结构的第二部分

```json
{
  "sub": "1234567890",
  "name": "John Doe",
  "admin": true
}
```

> 不要在JWT的Payload里面放敏感信息

### 5.3、Signature

前面两部分都是使用Base64进行编码的，即前端可以解开知道里面的信息。Signature 需要使用编码后的 header和 payload以及我们提供的一个密钥，然后使用header 中指定的签名算法(HS256)进行签名。签名的作用是保证JWT没有被篡改过

如: 	`HMACSHA256(base64UrlEncode( header) + ".”" + base64Ur1Encode(payload) , secret);`

1. 我们的Signature由我们的第一部分Header和第二部分Payload和第三部分secret密钥使用签名算法(HS256)生成一个签名
2. 我们发送我们的JWT给客户端，即第一部分Header和第二部分Payload和第三部分Signature
3. 客户端发送请求的时候我
   - 每一次都把第一部分Header和第二部分Payload加上secret密钥使用签名算法(HS256)生成第三部分Signature
   - 对比看第三部分的Signature是否相同
     - 第一部分，第二部分其中一部分不一致则对应生成的第三部分Signature也不一致
     - 第三部分修改，则我们拿第一部分和第二部分的，我们生成第三部分Signature也不会等于第三部分的被修改的值

4. 由一个secret开始的一个绝对不可修改的保密系统，是不可泄漏的服务器信息

最后一步签名的过程，实际上是对头部以及负载内容进行签名，防止内容被窜改。如果有人对头部以及负载的内容解码之后进行修改再进行编码，最后加上之前的签名组合形成新的JWT的话，那么服务器端会判断出新的头部和负载形成的签名和JWT附带上的签名是不一样的。如果要对新的头部和负载进行签名，在不知道服务器加密时用的密钥的话，得出来的签名也是不一样的。

**在这里大家一定会问一个问题：base 64是一种编码，是可逆的，那么我的信息不就被暴露了吗？**

是的。所以，在JWT中，不应该在负载里面加入任何敏感的数据。在上面的例子中，我们传输的是用户的User ID。这个值实际上不是什么敏感内容，一般情况下被知道也是安全的。但是像密码这样的内容就不能被放在JWT中了。如果将用户的密码放在了JWT中，那么怀有恶意的第﹐三方通过Base64解码就能很快地知道你的密码了。因此JWT适合用于向Web应用传递一些非敏感信息。JWT还经常用于设计用户认证和授权系统，甚至实现Web应用的单点登录。


![Encoded JWT](https://cdn.auth0.com/content/jwt/encoded-jwt3.png)

![JWT.io Debugger](https://cdn.auth0.com/blog/legacy-app-auth/legacy-app-auth-5.png)

## 6、常用方法

### 6.1、引进依赖

```xml
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt</artifactId>
    <version>0.9.1</version>
</dependency>
```

> 在这里只展示该Maven包下的对应方法

### 6.2 、JwtBuilder的方法介绍

在**`Jwts`**类中有一个静态方法叫做**`builder`**是专门来创建我们的token的

```java
    public static JwtBuilder builder() {
        return new DefaultJwtBuilder();
    }
```

而这个方法返回了一个**`DefaultJwtBuilder`**类，通过对应的idea工具，我们可以知道这个类实现了我们的**`JwtBuilder`**接口

![image-20211119140626426](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211119140626426.png)

**而我们的关键就在`JwtBuilder`，讲主要介绍接口中方法的定义**

#### **Head**

```json
{
  "alg": "HS256", //推荐使用算法
  "typ": "JWT"	  //类型
}
```

因此我们要进行头部的值设置

```java
JwtBuilder setHeaderParam(String name, Object value);
```

即如下写法

```java
Jwts.builder.setHeaderParam("tpy", "JWT");
```

并且 我们需要对token的算法进行规定

> Signs the constructed JWT using the specified algorithm with the specified key, producing a JWS.

```java
JwtBuilder signWith(SignatureAlgorithm alg, Key key);
```

即如下写法

```java
//secret是一个密钥，我们可以直接写在yml文件中
//secret: f4e2e52034348f86b67cde581c0f9eb5
JwtBuilder signWith(SignatureAlgorithm.HS512, secret);
```

#### **Payload**

我们的payload有两种不同的命名形式

- 第一种，纯String形式的payload形式(非JSON)

  > Sets the JWT's payload to be a plaintext (non-JSON) string. If you want the JWT body to be JSON

- 第二种，就是我们的JSON形式的声明形式

  > Sets the JWT payload to be a JSON Claims instance. 

  **但是这两种形式的命名是相互排斥的，即在一个token中我们只能用一种规则去命名我们的payload**

```java
 	JwtBuilder setPayload(String payload);
```

```java
    JwtBuilder setClaims(Claims claims);
    JwtBuilder setClaims(Map<String, Object> claims);
    JwtBuilder addClaims(Map<String, Object> claims);
```

> Claims即继承了**`Map<String, Object>`**方法的类，本质上我们还是使用对应的Map形式

其他如同

```java
	//设置JWT的发行者
    JwtBuilder setIssuer(String iss);
```

其实是

```java
    Claims claims = Jwts.claims().setIssuer("Joe");
    String jwt = Jwts.builder().setClaims(claims).compact();
```

其他的方法如同以下

```java
	//设置JWT的主体者
	JwtBuilder setSubject(String sub);
	//设置JWT的受众
    JwtBuilder setAudience(String aud);
```

都是设置**`Claim`**里面的值，再返回**`Claims`**类

#### **Signature**

生成token（1.编码 Header 和 Payload 2.生成签名 3.拼接字符串）

```java
	String compact();
```

#### else

我们不仅要定义我们的凭证，我们的凭证也要有对应的创建时间，凭证的许可时间，不能让用户一直能使用我们的凭证

```java
	//设置token的创建时间
	JwtBuilder setIssuedAt(Date iat);	
	//设置token过期时间
	JwtBuilder setNotBefore(Date nbf);
	JwtBuilder setExpiration(Date exp);
```

### 6.3、JwtParser的方法的使用

在**`Jwts`**类中有一个静态方法叫做**`parser()`**是专门来解析我们的token的

```java
    public static JwtParser parser() {
        return new DefaultJwtParser();
    }
```

而这个方法返回了一个**` DefaultJwtParser()`**类，通过对应的idea工具，我们可以知道这个类实现了我们的**`JwtParser()`**接口

![image-20211119162727994](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211119162727994.png)

**而我们的关键就在`JwtParser()`，讲主要介绍接口中方法的定义**

我们的解析Token需要两个重要的东西

- **我们设置的时候使用的secret**
- **我们传进来的Token**

```java
JwtParser setSigningKey(String base64EncodedKeyBytes);
```

>Sets the signing key used to verify any discovered JWS digital signature. If the specified JWT string is not a JWS (no signature), this key is not used.
>
>设置用于验证任何发现的JWS数字签名的签名密钥。如果指定的JWT字符串不是JWS(没有签名)，则不使用此密钥。

```java
    Jws<Claims> parseClaimsJws(String claimsJws)
            throws ExpiredJwtException, UnsupportedJwtException, MalformedJwtException, SignatureException, IllegalArgumentException;
}
```

>Parses the specified compact serialized JWS string based on the builder's current configuration state and returns the resulting Claims JWS instance.
>
>基于构建器的当前配置状态解析指定的紧凑序列化JWS字符串，并返回结果Claims JWS实例。

```java
getBody();
```

>Returns the JWT body, either a String or a Claims instance.
>
>返回Claims类实例

## 7、使用JWT

### 7.1、构建JWT

```java
//secret已经在yml里面定义  
public String generateToken() {
    Date nowDate = new Date();
	Date expireDate = new Date(nowDate.getTime() + expire * 1000);
    return Jwts.builder()
                .setHeaderParam("typ", "JWT") 
                .setSubject(userId+"")	 //设置每一个发行者对应的主体id是用户的id		
                .setIssuedAt(nowDate）				
                .setExpiration(expireDate)			
                .signWith(SignatureAlgorithm.HS512, secret) 
                .compact();							 
  }
```

### 7.2、解析JWT

```java
  public Claims getClaimByToken(String token) {
	try {
	  return Jwts.parser()
			  .setSigningKey(secret)
			  .parseClaimsJws(token)
			  .getBody();
	}catch (Exception e){
	  log.debug("validate is token error ", e);
	  return null;
	}
  }
```

## 8、封装工具类

在这里我们是使用的是

```xml
<!-- jwt -->
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt</artifactId>
    <version>0.9.1</version>
</dependency>
```

```java
package com.ceit.blog.util;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

import java.util.Date;

@Slf4j
@Data
@Component
@ConfigurationProperties(prefix = "ceit.jwt")
public class JwtUtils {

  private String secret;
  private long expire;
  private String header;

  public String generateToken(long userId) {
	Date nowDate = new Date();
	Date expireDate = new Date(nowDate.getTime() + expire * 1000);

	return Jwts.builder()
			.setHeaderParam("typ", "JWT") 		//header，有默认值
			.setSubject(userId+"")				//payload
			.setIssuedAt(nowDate)				//设置签发时间
			.setExpiration(expireDate)			//指定令牌过期时间
			.signWith(SignatureAlgorithm.HS512, secret) //签名
			.compact();							// 生成token（1.编码 Header 和 Payload 2.生成签名 3.拼接字符串）
  }
  public Claims getClaimByToken(String token) {
	try {
	  return Jwts.parser()
			  .setSigningKey(secret)
			  .parseClaimsJws(token)
			  .getBody();
	}catch (Exception e){
	  log.debug("validate is token error ", e);
	  return null;
	}
  }

  /**
   * token是否过期
   * @return  true：过期
   */
  public boolean isTokenExpired(Date expiration) {
	return expiration.before(new Date());
  }
}

```

