 

# 1. 配置文件

## 1.1 文件类型

### 1.1.1 properties

同以前的properties用法

### 1.1.2 yaml

#### 1、简介

YAML 是 "YAML Ain't Markup Language"（YAML 不是一种标记语言）的递归缩写。在开发的这种语言时，YAML 的意思其实是："Yet Another Markup Language"（仍是一种标记语言）。 



非常适合用来做以数据为中心的配置文件



#### 2、基本语法

- key: value；kv之间有空格
- 大小写敏感

- 使用缩进表示层级关系
- 缩进不允许使用tab，只允许空格

- 缩进的空格数不重要，只要相同层级的元素左对齐即可
- '#'表示注释

- 字符串无需加引号，如果要加，''与""表示字符串内容 会被 转义/不转义



#### 3、数据类型



- 字面量：单个的、不可再分的值。date、boolean、string、number、null

```yaml
k: v
```

- 对象：键值对的集合。map、hash、set、object 

```yaml
行内写法：  k: {k1:v1,k2:v2,k3:v3}
#或
k: 
  k1: v1
  k2: v2
  k3: v3
```

- 数组：一组按次序排列的值。array、list、queue

```yaml
行内写法：  k: [v1,v2,v3]
#或者
k:
 - v1
 - v2
 - v3
```

#### 4、示例

```java
@Data
public class Person {
	
	private String userName;
	private Boolean boss;
	private Date birth;
	private Integer age;
	private Pet pet;
	private String[] interests;
	private List<String> animal;
	private Map<String, Object> score;
	private Set<Double> salarys;
	private Map<String, List<Pet>> allPets;
}

@Data
public class Pet {
	private String name;
	private Double weight;
}
```



```yaml
# yaml表示以上对象
person:
  userName: zhangsan
  #双引号会把\n作为换行输出，单引号会把\n作为字符串输出
  #双引号不会转义，单引号会转义
  boss: false
  birth: 2019/12/12 20:12:33
  age: 18
  pet: 
    name: tomcat
    weight: 23.4
  interests: [篮球,游泳]
  animal: 
    - jerry
    - mario
  score:
    english: 
      first: 30
      second: 40
      third: 50
    math: [131,140,148]
    chinese: {first: 128,second: 136}
  salarys: [3999,4999.98,5999.99]
  allPets:
    sick:
      - {name: tom}
      - {name: jerry,weight: 47}
    health: [{name: mario,weight: 47}]
```



## 1.2 配置提示

自定义的类和配置文件绑定一般没有提示。我们在配置编写的时候我们会有很多bean但是没有提示特别蛋疼

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-configuration-processor</artifactId>
    <optional>true</optional>
</dependency>


<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
            <configuration>
                <excludes>
                    <exclude>
                        <groupId>org.springframework.boot</groupId>
                        <artifactId>spring-boot-configuration-processor</artifactId>
                    </exclude>
                </excludes>
            </configuration>
        </plugin>
    </plugins>
</build>
```



# 2. web开发

![image-20211004192329322](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211004192329322.png)





## 2.1 SpringMVC自动配置概览

Spring Boot provides auto-configuration for Spring MVC that **works well with most applications.(大多场景我们都无需自定义配置)**

The auto-configuration adds the following features on top of Spring’s defaults:

- Inclusion of `ContentNegotiatingViewResolver` and `BeanNameViewResolver` beans.

- - 内容协商视图解析器和BeanName视图解析器

- Support for serving static resources, including support for WebJars (covered [later in this document](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-spring-mvc-static-content))).

- - 静态资源（包括webjars）

- Automatic registration of `Converter`, `GenericConverter`, and `Formatter` beans.

- - 自动注册 `Converter，GenericConverter，Formatter `

- Support for `HttpMessageConverters` (covered [later in this document](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-spring-mvc-message-converters)).

- - 支持 `HttpMessageConverters` （后来我们配合内容协商理解原理）

- Automatic registration of `MessageCodesResolver` (covered [later in this document](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-spring-message-codes)).

- - 自动注册 `MessageCodesResolver` （国际化用）

- Static `index.html` support.

- - 静态index.html 页支持

- Custom `Favicon` support (covered [later in this document](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-spring-mvc-favicon)).

- - 自定义 `Favicon`  

- Automatic use of a `ConfigurableWebBindingInitializer` bean (covered [later in this document](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-spring-mvc-web-binding-initializer)).

- - 自动使用 `ConfigurableWebBindingInitializer` ，（DataBinder负责将请求数据绑定到JavaBean上）

>If you want to keep those Spring Boot MVC customizations and make more [MVC customizations](https://docs.spring.io/spring/docs/5.2.9.RELEASE/spring-framework-reference/web.html#mvc) (interceptors, formatters, view controllers, and other features), you can add your own `@Configuration` class of type `WebMvcConfigurer` but **without** `@EnableWebMvc`.
>
>**不用@EnableWebMvc注解。使用** `@Configuration` **+** `WebMvcConfigurer` **自定义规则**

在配置类@Configuration和implements WebMvcConfigurer以后进行方法重写，我们重写其中的方法

>If you want to provide custom instances of `RequestMappingHandlerMapping`, `RequestMappingHandlerAdapter`, or `ExceptionHandlerExceptionResolver`, and still keep the Spring Boot MVC customizations, you can declare a bean of type `WebMvcRegistrations` and use it to provide custom instances of those components.
>
>**声明** `WebMvcRegistrations`**改变默认底层组件**



>If you want to take complete control of Spring MVC, you can add your own `@Configuration` annotated with `@EnableWebMvc`, or alternatively add your own `@Configuration`-annotated `DelegatingWebMvcConfiguration` as described in the Javadoc of `@EnableWebMvc`.
>
>**使用** `@EnableWebMvc+@Configuration+DelegatingWebMvcConfiguration 全面接管SpringMVC`





## 2.2 简单功能分析

### 2.2.1 静态资源访问

#### 1、静态资源目录

只要静态资源放在类路径下： called `/static` (or `/public` or `/resources` or `/META-INF/resources`

访问 ： 当前项目根路径/ + 静态资源名 



原理： 静态映射/**。

请求进来，先去找Controller看能不能处理。不能处理的所有请求又都交给静态资源处理器。静态资源也找不到则响应404页面



改变默认的静态资源路径

```yaml
spring:
  mvc:
    static-path-pattern: /res/**
    #这里的static-locations标记的是设置某个路径下才是属于静态资源，这里的static-locations是数组的形式，我们可以设置多个文件夹下面的都说静态资源，，记住前后都有/哦
  web:
    resources:
      static-locations: [classpath:/haha/]
```

> 非常重要，假如我们写了一个Web应用，应用里面有超多静态资源，还有一些动态请求，但Web应用里面有一些拦截器。比如我们的登入拦截器，只有登入以后才能访问一些动态请求，假如我们拦截的/**相当于把静态资源也拦截住了，为了拦截器配置方便，令我们的静态资源访问带一个前缀，令拦截器放行以指定路径的所有请求

#### 2、静态资源访问前缀

默认无前缀

```yaml
spring:
  mvc:
    static-path-pattern: /res/**
```

当前项目 + static-path-pattern + 静态资源名 = 静态资源文件夹下找



#### 3、webjar

自动映射 /[webjars](http://localhost:8080/webjars/jquery/3.5.1/jquery.js)/**

https://www.webjars.org/

```xml
        <dependency>
            <groupId>org.webjars</groupId>
            <artifactId>jquery</artifactId>
            <version>3.5.1</version>
        </dependency>
```

访问地址：[http://localhost:8080/webjars/**jquery/3.5.1/jquery.js**](http://localhost:8080/webjars/jquery/3.5.1/jquery.js)   后面地址要按照依赖里面的包路径



### 2.2.2 欢迎页支持

- 静态资源路径下  index.html

- - 可以配置静态资源路径
  - 但是不可以配置静态资源的访问前缀。否则导致 index.html不能被默认访问

```yaml
spring:
#  mvc:
#    static-path-pattern: /res/**  如果加上这个，我们也必须加上/res前缀才可以访问，这个会导致welcome page功能失效。

  resources:
    static-locations: [classpath:/haha/]
```

- controller能处理/index

  

### 2.2.3 自定义 `Favicon`

favicon.ico 放在静态资源目录下即可。

```yaml
spring:
#  mvc:
#    static-path-pattern: /res/**   这个会导致 Favicon 功能失效
```

### 2.2.4 静态资源配置原理

- SpringBoot启动默认加载  xxxAutoConfiguration 类（自动配置类）
- SpringMVC功能的自动配置类 WebMvcAutoConfiguration，生效
- 以下是配置类详解

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnWebApplication(type = Type.SERVLET)
@ConditionalOnClass({ Servlet.class, DispatcherServlet.class, WebMvcConfigurer.class })
@ConditionalOnMissingBean(WebMvcConfigurationSupport.class)
@AutoConfigureOrder(Ordered.HIGHEST_PRECEDENCE + 10)
@AutoConfigureAfter({ DispatcherServletAutoConfiguration.class, TaskExecutionAutoConfiguration.class,
		ValidationAutoConfiguration.class })
public class WebMvcAutoConfiguration {}
```

- 生效以后给给容器中配了什么呢

```java
	@Configuration(proxyBeanMethods = false)
	@Import(EnableWebMvcConfiguration.class)
	@EnableConfigurationProperties({ WebMvcProperties.class, ResourceProperties.class })
	@Order(0)
	public static class WebMvcAutoConfigurationAdapter implements WebMvcConfigurer {}
```

- 配置文件的相关属性和xxx进行了绑定。WebMvcProperties==**spring.mvc**、ResourceProperties==**spring.resources**

#### 1、配置类只有一个有参构造器

配置类只有一个有参构造器，这里我们用 WebMvcAutoConfigurationAdapter来举例子，我们的有参构造器所有参数的值都会从容器中确定

```java
//ResourceProperties resourceProperties；获取和spring.resources绑定的所有的值的对象
//WebMvcProperties mvcProperties 获取和spring.mvc绑定的所有的值的对象
//ListableBeanFactory beanFactory Spring的beanFactory即容器
//HttpMessageConverters 找到所有的HttpMessageConverters
//ResourceHandlerRegistrationCustomizer 找到 资源处理器的自定义器。(重点)
//DispatcherServletPath  
//ServletRegistrationBean   给应用注册Servlet、Filter....
	public WebMvcAutoConfigurationAdapter(ResourceProperties resourceProperties, WebMvcProperties mvcProperties,
				ListableBeanFactory beanFactory, ObjectProvider<HttpMessageConverters> messageConvertersProvider,
				ObjectProvider<ResourceHandlerRegistrationCustomizer> resourceHandlerRegistrationCustomizerProvider,
				ObjectProvider<DispatcherServletPath> dispatcherServletPath,
				ObjectProvider<ServletRegistrationBean<?>> servletRegistrations) {
			this.resourceProperties = resourceProperties;
			this.mvcProperties = mvcProperties;
			this.beanFactory = beanFactory;
			this.messageConvertersProvider = messageConvertersProvider;
			this.resourceHandlerRegistrationCustomizer = resourceHandlerRegistrationCustomizerProvider.getIfAvailable();
			this.dispatcherServletPath = dispatcherServletPath;
			this.servletRegistrations = servletRegistrations;
		}
```





#### 2、资源处理的默认规则

```java
@Override
		public void addResourceHandlers(ResourceHandlerRegistry registry) {
			if (!this.resourceProperties.isAddMappings()) {  //拿到spring.resources下绑定的所有配置的东西然后拿AddMappings（默认是true)
				logger.debug("Default resource handling disabled");
				return;
			}
			Duration cachePeriod = this.resourceProperties.getCache().getPeriod();
			CacheControl cacheControl = this.resourceProperties.getCache().getCachecontrol().toHttpCacheControl();
			//webjars的规则
            if (!registry.hasMappingForPattern("/webjars/**")) {
				customizeResourceHandlerRegistration(registry.addResourceHandler("/webjars/**")
						.addResourceLocations("classpath:/META-INF/resources/webjars/")
						.setCachePeriod(getSeconds(cachePeriod)).setCacheControl(cacheControl));
			}
            
            //
			String staticPathPattern = this.mvcProperties.getStaticPathPattern();
			if (!registry.hasMappingForPattern(staticPathPattern)) {
				customizeResourceHandlerRegistration(registry.addResourceHandler(staticPathPattern)
						.addResourceLocations(getResourceLocations(this.resourceProperties.getStaticLocations()))//resourceProperties
						.setCachePeriod(getSeconds(cachePeriod)).setCacheControl(cacheControl));
			}
		}
```

```yaml
spring:
#  mvc:
#    static-path-pattern: /res/**
  resources:
    add-mappings: false   禁用所有静态资源规则
```

```java
@ConfigurationProperties(prefix = "spring.resources", ignoreUnknownFields = false)
public class ResourceProperties {

	private static final String[] CLASSPATH_RESOURCE_LOCATIONS = { "classpath:/META-INF/resources/",
			"classpath:/resources/", "classpath:/static/", "classpath:/public/" };
	
	/**
	 * Locations of static resources. Defaults to classpath:[/META-INF/resources/,
	 * /resources/, /static/, /public/].
	 */
	private String[] staticLocations = CLASSPATH_RESOURCE_LOCATIONS; //对应的默认值，也就是对应的四个位置
```



#### 3、欢迎页的处理规则

```java
	//HandlerMapping：SpringMvc的核心组件，处理器映射。保存了每一个Handler能处理哪些请求。	

	@Bean
		public WelcomePageHandlerMapping welcomePageHandlerMapping(ApplicationContext applicationContext,
				FormattingConversionService mvcConversionService, ResourceUrlProvider mvcResourceUrlProvider) {
			WelcomePageHandlerMapping welcomePageHandlerMapping = new WelcomePageHandlerMapping(
					new TemplateAvailabilityProviders(applicationContext), applicationContext, getWelcomePage(),
					this.mvcProperties.getStaticPathPattern());
			welcomePageHandlerMapping.setInterceptors(getInterceptors(mvcConversionService, mvcResourceUrlProvider));
			welcomePageHandlerMapping.setCorsConfigurations(getCorsConfigurations());
			return welcomePageHandlerMapping;
		}
//下面是WelcomePageHandlerMapping的构造方法
	WelcomePageHandlerMapping(TemplateAvailabilityProviders templateAvailabilityProviders,
			ApplicationContext applicationContext, Optional<Resource> welcomePage, String staticPathPattern) {
		if (welcomePage.isPresent() && "/**".equals(staticPathPattern)) {
            //要用欢迎页功能，必须是/**
			logger.info("Adding welcome page: " + welcomePage.get());
			setRootViewName("forward:index.html");
		}
		else if (welcomeTemplateExists(templateAvailabilityProviders, applicationContext)) {
            // 调用Controller  /index
			logger.info("Adding welcome page template: index");
			setRootViewName("index");
		}
	}
```

#### 4、favicon

浏览器会发送/favicon.ico请求获取到图标，整个session期间不再获取

## 2.3 请求参数处理



### 2.3.1 请求映射

什么是请求映射，我们在我们的控制器上面声明它是`@RestController`

#### 1、rest使用与原理

- `@xxxMapping；`
- Rest风格支持（*使用**HTTP**请求方式动词来表示对资源的操作*）

  - *以前：/getUser*  *获取用户*    */deleteUser* *删除用户*   */editUser*  *修改用户*      */saveUser* *保存用户*
  - *现在： /user*    *GET-获取用户*    *DELETE-删除用户*     *PUT-修改用户*      *POST-保存用户*，利用请求方式的不同来进行操作
  - 核心Filter；HiddenHttpMethodFilter

  - 用法： 表单`method=post`，隐藏域 _method=put
  - SpringBoot中`手动开启`

  - 扩展：如何把_method 这个名字换成我们自己喜欢的。

```java
    @RequestMapping(value = "/user",method = RequestMethod.GET)
    public String getUser(){
        return "GET-张三";
    }

    @RequestMapping(value = "/user",method = RequestMethod.POST)
    public String saveUser(){
        return "POST-张三";
    }


    @RequestMapping(value = "/user",method = RequestMethod.PUT)
    public String putUser(){
        return "PUT-张三";
    }

    @RequestMapping(value = "/user",method = RequestMethod.DELETE)
    public String deleteUser(){
        return "DELETE-张三";
    }

//为什么要手动开启,因为默认是关闭的
	@Bean
	@ConditionalOnMissingBean(HiddenHttpMethodFilter.class)
	@ConditionalOnProperty(prefix = "spring.mvc.hiddenmethod.filter", name = "enabled", matchIfMissing = false)
	public OrderedHiddenHttpMethodFilter hiddenHttpMethodFilter() {
		return new OrderedHiddenHttpMethodFilter();
	}


//判断我们的@ConditionalOnMissingBean(HiddenHttpMethodFilter.class)，我们可以自定义这个HiddenHttpMethodFilter.class,设置一个配置类给methodFilter.setMethodParam(""),重写MethodParam
    @Bean
    public HiddenHttpMethodFilter hiddenHttpMethodFilter(){
        HiddenHttpMethodFilter methodFilter = new HiddenHttpMethodFilter();
        methodFilter.setMethodParam("_m");
        return methodFilter;
    }
```

Rest原理（表单提交要使用REST的时候）

- 表单提交会带上**_method=PUT**
- **请求过来被**HiddenHttpMethodFilter拦截
  - 请求是否正常，并且是POST
    - 获取到**_method**的值，在底层帮你转换成大写的。
    - 兼容以下请求；**PUT**.**DELETE**.**PATCH**
    - **原生request（post），包装模式requesWrapper重写了getMethod方法，返回的是传入的值。**
    - **过滤器链放行的时候用wrapper。以后的方法调用getMethod是调用requesWrapper的。**



**Rest使用客户端工具，**

- 如PostMan直接发送Put、delete等方式请求，无需Filter。

开启页面表单的Rest功能：

```yaml
spring:
  mvc:
    hiddenmethod:
      filter:
        enabled: true  
```

#### 2、请求映射原理

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603181171918-b8acfb93-4914-4208-9943-b37610e93864.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_27%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

我们发现在`HttplServletBean`里面没有重写`doGet`和`doPost`方法，而是在`FrameworkServlet`重写，而且调用了`processRequest`方法，追究到`processRequest`发现了`doService`方法，而`doService`方法是一个抽象方法，在`DispatcherServlet`里面进行实现，调用了`doDispatch`方法

**我们接下来重点研究这个`doDispatch`方法，我们来看这个这个代码**

```java
 //传入原生的HttpServletRequest request, HttpServletResponse response方法
protected void doDispatch(HttpServletRequest request, HttpServletResponse response) throws Exception {  
		HttpServletRequest processedRequest = request;
		HandlerExecutionChain mappedHandler = null;
		boolean multipartRequestParsed = false;

		WebAsyncManager asyncManager = WebAsyncUtils.getAsyncManager(request);

		try {
			ModelAndView mv = null;
			Exception dispatchException = null;

			try {
				processedRequest = checkMultipart(request);
				multipartRequestParsed = (processedRequest != request);

				// 找到当前请求使用哪个Handler（Controller的方法）处理
				mappedHandler = getHandler(processedRequest);
                
                //HandlerMapping：处理器映射。/xxx->>xxxx
```

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603181460034-ba25f3c0-9cfd-4432-8949-3d1dd88d8b12.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_14%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

**WelcomePageHandlerMapping**：保存了主页的映射规则。

**RequestMappingHandlerMapping**：保存了所有@RequestMapping 和handler的映射规则。

我们按照循环挨个尝试所有的HandlerMapping看是否有请求信息。

如果有多个会报错。

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603181662070-9e526de8-fd78-4a02-9410-728f059d6aef.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_48%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

所有的请求映射都在HandlerMapping中。

- SpringBoot自动配置欢迎页的 WelcomePageHandlerMapping 。访问 /能访问到index.html；
- SpringBoot自动配置了默认 的 RequestMappingHandlerMapping
- 请求进来，**挨个尝试所有的HandlerMapping看是否有请求信息**。

  - 如果有就找到这个请求对应的handler
  - 如果没有就是下一个 HandlerMapping
- 我们需要一些自定义的映射处理，我们也可以自己给容器中放**HandlerMapping**。自定义 **HandlerMapping**，比如我们在v1下的uesr和v2的user，规定我们的v1去哪个去找，v2去哪个去找

```java
	protected HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception {
		if (this.handlerMappings != null) {
			for (HandlerMapping mapping : this.handlerMappings) {
				HandlerExecutionChain handler = mapping.getHandler(request);
				if (handler != null) {
					return handler;
				}
			}
		}
		return null;
	}
```

### 2.3.2 普通参数与基本注解

#### 1、注解

`@PathVariable、@RequestHeader`、@ModelAttribute、`@RequestParam、@MatrixVariable`、@CookieValue、`@RequestBody`

> 我们这里统一用@RestController测试

- **@PathVariable（路径变量）**

```java
@GetMapping("/car/{id}/owner/{username}")
//@PathVariable代表按照路径变量的值随机变化
//@PathVariable在map方法中有对应的用法，可以把url中的key value值保存下来，但是kv必须是String:String
///car/3/owner/lisi
    public Map<String,Object> getCar(@PathVariable("id") Integer id,
                                     @PathVariable("username") String name,
                                     @PathVariable Map<String,String> pv){
        Map<String,Object> map = new HashMap<>();

        map.put("id",id);
        map.put("name",name);
        map.put("pv",pv);	

        return map;
    }
```

返回到客户端数据如图：

![image-20211006171205648](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006171205648.png)



- **@RequestHeader（请求头）**

```java
@GetMapping("/car/{id}/owner/{username}")
//@RequestHeader在map方法中有对应的用法，可以把url中的key value值保存下来，但是kv必须是String:String
    public Map<String,Object> getCar(@RequestHeader Map<String,String> header,
                                     @RequestHeader("User-Agent") String userAgent){ //带key就是只拿某一个，不带就是全要
        Map<String,Object> map = new HashMap<>();

        map.put("userAgent",userAgent);
        map.put("headers",header);	

        return map;
    }
```

返回到客户端数据如图：

![image-20211006171809007](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006171809007.png)



- **@RequestParam（请求参数）**

```java
	@GetMapping("/car/{id}/owner/{username}")
//@RequestParam在map方法中有对应的用法，可以把url中的key value值保存下来，但是kv必须是String:String
//<a href="car/3/owner/lisi?age=18&inters=basketball&inters=game">想要获取age和inters的值
    public Map<String,Object> getCar(@RequestParam("age") Integer age,
                                     @RequestParam("inters") List<String> inters,
                                     @RequestParam Map<String,String> params){
        Map<String,Object> map = new HashMap<>();   
        
        map.put("age",age);
        map.put("inters",inters);
        map.put("params",params);
        
        return map;
    }
```

返回到客户端数据如图：

![image-20211006172830814](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006172830814.png)



- **@CookieValue(cookie的值)**

```java
	@GetMapping("/car/{id}/owner/{username}")
//@RequestParam在map方法中有对应的用法，可以把url中的key value值保存下来，但是kv必须是String:String
//<a href="car/3/owner/lisi?age=18&inters=basketball&inters=game">想要获取age和inters的值
    public Map<String,Object> getCar(@CookieValue("_ga") String _ga,
                                     @CookieValue("_ga") Cookie cookie){
        Map<String,Object> map = new HashMap<>();   
        
        map.put("_ga",_ga); //某个cookie值
        System.out.println(cookie.getName()+"===>"+cookie.getValue()); //整个cookie拿过来
        return map;
    }
```

控制台：![image-20211006173424479](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006173424479.png)

客户端数据：![image-20211006173506440](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006173506440.png)



- **@RequestBody(请求体的值，只有post请求才有请求体）**

这里假设是我们有一个表格，提交的方法是post

```java
 @PostMapping("/save")
    public Map postMethod(@RequestBody String content){
        Map<String,Object> map = new HashMap<>();
        map.put("content",content);
        return map;
    }
```

客户端数据：![image-20211006173833598](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006173833598.png)

- **@RequestAttribute**

与request.getAttribute同效果

```java
@Controller
public class RequestController {
@GetMapping("/goto")
    public String goToPage(HttpServletRequest request){
    request.setAttribute("msg","成功");
    request.setAttribute("code",200);
    return "forward:/success";
}
@ResponseBody
@GetMapping("/success")
public Map success(@RequestAttribute("msg") String msg,
                   @RequestAttribute("code") Integer code,
                   HttpServletRequest request){
    Object msg1 = request.getAttribute("msg");
    HashMap<String, Object> map = new HashMap<>();

    map.put("reqMethod_msg",msg1);
    map.put("annotation_msg",msg);
    return map;
}
}
```

客户端数据：

![image-20211006193230396](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211006193230396.png)



- **@MatrixVariable（矩阵变量）**

如何使用：

矩阵变量要在SpringBooot手动开启，对于路径的处理。`UrlPathHelper`进行解析。`removeSemicolonContent`（移除分号内容）支持矩阵变量的

```java
public void configurePathMatch(PathMatchConfigurer configurer) { //在web自动装配里面有configurePathMatch方法
            if (this.mvcProperties.getPathmatch().getMatchingStrategy() == MatchingStrategy.PATH_PATTERN_PARSER) {
                configurer.setPatternParser(new PathPatternParser());
            }

            configurer.setUseSuffixPatternMatch(this.mvcProperties.getPathmatch().isUseSuffixPattern());
            configurer.setUseRegisteredSuffixPatternMatch(this.mvcProperties.getPathmatch().isUseRegisteredSuffixPattern());
            this.dispatcherServletPath.ifAvailable((dispatcherPath) -> {
                String servletUrlMapping = dispatcherPath.getServletUrlMapping();
                if (servletUrlMapping.equals("/") && this.singleDispatcherServlet()) {
                    UrlPathHelper urlPathHelper = new UrlPathHelper();   //其中有UrlPathHelper 
                    urlPathHelper.setAlwaysUseFullPath(true);
                    configurer.setUrlPathHelper(urlPathHelper);
                }

            });
        }
```

```java
  private boolean removeSemicolonContent = true; //UrlPathHelper的一个重要属性，意思是移除分号内容
  public void setRemoveSemicolonContent(boolean removeSemicolonContent) { //对应的方法，因从我们的是默认关闭的
        this.checkReadOnly();
        this.removeSemicolonContent = removeSemicolonContent;
    }
```

```java
//1. 继承WebMvcConfigurer
public void configurePathMatch(PathMatchConfigurer configurer){
UrlPathHelper urlPathHelper =new UrlPathHelper();
urlPathHelper.setRemoveSemicolonContest(false);
configurer.setUrlPathHelper(urlPathHelper);}


//2. 不继承
@Bean
public WebMvcConfigurer  webMvcConfigurer(){
return new webMvcConfigurer(){
//重写configurePathMatch方法
    public void configurePathMatch(PathMatchConfigurer configurer){
UrlPathHelper urlPathHelper =new UrlPathHelper();
urlPathHelper.setRemoveSemicolonContest(false);
configurer.setUrlPathHelper(urlPathHelper);}
};
}
```

1. 语法： 

   - 请求路径：`/cars/{path}?xx=yy?aa=cc `

     这种叫查询字符串，用`@RequestParam`处理

   -  请求路径：`/cars/sell;low=34;brand=byd,audi,yd `

     这种分号写法我们叫做矩阵变量

2. 假如在页面开发时候，Session里面有session.set(a,b)，设了一个a,a的值是b，每一个每一个Session都有一个Sessionid我们叫做jsessionid，这个id保存在cookie里面，而cookie每次法发请求都会携带，每次根据cookie来得id得到Session信息

   - cookie被禁用了，我们还想访问，我们怎么访问？我们要用路径重写：/abc;jsessionid=xxxx，即cookie的值使用矩阵变量进行传递，一个key对应一个v，当一个key对应多个v时候v要用逗号分开

```java
//路径变量默认写成{path}
// /cars/sell;low=34;brand=byd,audi,yd
    @GetMapping("/cars/{path}")
    public Map carsSell(@MatrixVariable("low") Integer low,
                        @MatrixVariable("brand") List<String> brand,
                        @PathVariable("path") String path){
        //注意这里是@PathVariable
        Map<String,Object> map = new HashMap<>();

        map.put("low",low); //是34
        map.put("brand",brand); //是byd,audi,yd
        map.put("path",path); //得到的就是sell
        return map;
    }

// /boss/1;age=20/2;age=10

    @GetMapping("/boss/{bossId}/{empId}")
    public Map boss(@MatrixVariable(value = "age",pathVar = "bossId") Integer bossAge,
                    @MatrixVariable(value = "age",pathVar = "empId") Integer empAge){
        Map<String,Object> map = new HashMap<>();

        map.put("bossAge",bossAge);
        map.put("empAge",empAge);
        return map;

    }

}
```

#### 2、Servlet API

WebRequest(相当于request和respond组合)、ServletRequest、MultipartRequest、 HttpSession、javax.servlet.http.PushBuilder、Principal、InputStream、Reader、HttpMethod、Locale、TimeZone、ZoneId



**`ServletRequestMethodArgumentResolver` 来负责以上的类型的参数的解析功能**

```java
@Override
	public boolean supportsParameter(MethodParameter parameter) {
		Class<?> paramType = parameter.getParameterType();
		return (WebRequest.class.isAssignableFrom(paramType) ||
				ServletRequest.class.isAssignableFrom(paramType) ||
				MultipartRequest.class.isAssignableFrom(paramType) ||
				HttpSession.class.isAssignableFrom(paramType) ||
				(pushBuilder != null && pushBuilder.isAssignableFrom(paramType)) ||
				Principal.class.isAssignableFrom(paramType) ||
				InputStream.class.isAssignableFrom(paramType) ||
				Reader.class.isAssignableFrom(paramType) ||
				HttpMethod.class == paramType ||
				Locale.class == paramType ||
				TimeZone.class == paramType ||
				ZoneId.class == paramType);
	}
```



#### 3、复杂参数：

**Map**、**Model、**Errors/BindingResult、**RedirectAttributes（ 重定向携带数据）**、**ServletResponse（response响应）**、SessionStatus、UriComponentsBuilder、ServletUriComponentsBuilder

> map、model里面的数据会被放在request的请求域里面，和request.setAttribute是一个道理的，我们都可以用request.getAttribute来取出来

```java
Map<String,Object> map,  Model model, HttpServletRequest request 都是可以给request域中放数据，
```

下面我们来分析它的原理：

**Map、Model类型的参数**，会返回 mavContainer.getModel（）去找到BindingAwareModelMap ，其中这个BindingAwareModelMap是Model 也是Map

最后**mavContainer**.getModel();最后获取到对应的类型的数值

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603271442869-63b4c3c7-c721-4074-987d-cbe5999273ae.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_28%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603271678813-d8e1a1e5-94fa-412c-a7f1-6f27174fd127.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_20%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

> Map和Model都是同一个对象5845

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603271813894-037be041-92a5-49af-a49c-c350b3dd587a.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_27%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



#### 4、自定义对象参数：

可以自动类型转换与格式化，可以级联封装，关于Spring如何封装到对象的，无论是get和post的都可以和对象绑定

> 一定名字要相同

```java
/**
 *     姓名： <input name="userName"/> <br/>
 *     年龄： <input name="age"/> <br/>
 *     生日： <input name="birth"/> <br/>
 *     宠物姓名：<input name="pet.name"/><br/>
 *     宠物年龄：<input name="pet.age"/>
 */
@Data
public class Person {
    
    private String userName;
    private Integer age;
    private Date birth;
    private Pet pet;
    
}

@Data
public class Pet {

    private String name;
    private String age;

}

```

### 2.3.3 参数处理原理

- HandlerMapping中找到能处理请求的Handler（Controller.method()）
- 为当前Handler 找一个适配器 HandlerAdapter；最后 HandlerAdapter会调用handle方法来处理目标方法，**RequestMappingHandlerAdapter**

- 适配器执行目标方法并确定方法参数的每一个值

下面介绍我们的HandlerAdapter

#### 1、HandlerAdapter

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603262942726-107353bd-f8b7-44f6-93cf-2a3cad4093cf.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_18%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

0 - 支持方法上标注@RequestMapping （默认找到第一个）

1 - 支持函数式编程的

xxxxxx

#### 2、执行目标方法

```java
// Actually invoke the handler.
//DispatcherServlet里面的doDispatch方法
mv = ha.handle(processedRequest, response, mappedHandler.getHandler());
```

```java
mav = invokeHandlerMethod(request, response, handlerMethod); //执行目标方法,但首先需要提供一个参数解析器，HandlerMethodArgumentResolver
```

```java
//执行方法内部第一步：
//我们的ServletInvocableHandlerMethod把参数解析器和返回值处理器提前加载
//invokeForRequest执行我们的请求，是真正执行目标的方法！！它是在ServletInvocableHandlerMethod里面的！
Object returnValue = invokeForRequest(webRequest, mavContainer, providedArgs);

//执行方法内部第二步：
//如果想真正执行目标方法我们需要知道每一个参数的值是什么
//获取方法的参数值
Object[] args = getMethodArgumentValues(request, mavContainer, providedArgs);
```



#### 3、参数解析器-HandlerMethodArgumentResolver

确定将要执行的目标方法的每一个参数的值是什么;

**SpringMVC目标方法能写多少种参数类型。取决于参数解析器。**

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603263283504-85bbd4d5-a9af-4dbf-b6a2-30b409868774.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_20%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603263394724-33122714-9d06-42ec-bf45-e440e8b49c05.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_23%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

工作步骤：

- 当前解析器是否支持解析这种参数
- 支持就调用 resolveArgument



#### 4、返回值处理器

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603263524227-386da4be-43b1-4b17-a2cc-8cf886346af9.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_22%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

对应我们能写的返回值的类型

#### 5、如何确定目标方法每一个参数的值

```java
								============InvocableHandlerMethod===============
protected Object[] getMethodArgumentValues(NativeWebRequest request, @Nullable ModelAndViewContainer mavContainer,
			Object... providedArgs) throws Exception {

		MethodParameter[] parameters = getMethodParameters();  //获取到所有方法的参数声明，参数的详细信息，如标了什么注解，是什么类型等等
		if (ObjectUtils.isEmpty(parameters)) { //如果是空的我们直接返回
			return EMPTY_ARGS;
		}

		Object[] args = new Object[parameters.length]; //参数有几个这个数组就有多长
		for (int i = 0; i < parameters.length; i++) { //挨个遍历
			MethodParameter parameter = parameters[i];
			parameter.initParameterNameDiscovery(this.parameterNameDiscoverer);
			args[i] = findProvidedArgument(parameter, providedArgs);
			if (args[i] != null) {
				continue;
			}
			if (!this.resolvers.supportsParameter(parameter)) {//判断参数是否符合解析器里面的内容，其实内部是挨个遍历看看谁能支持，我们在5.1介绍
				throw new IllegalStateException(formatArgumentError(parameter, "No suitable resolver"));
			}
			try {
                //重点
				args[i] = this.resolvers.resolveArgument(parameter, mavContainer, request, this.dataBinderFactory);
			}
			catch (Exception ex) {
				// Leave stack trace for later, exception may actually be resolved and handled...
				if (logger.isDebugEnabled()) {
					String exMsg = ex.getMessage();
					if (exMsg != null && !exMsg.contains(parameter.getExecutable().toGenericString())) {
						logger.debug(formatArgumentError(parameter, exMsg));
					}
				}
				throw ex;
			}
		}
		return args;
	}
```

##### 5.1、挨个判断所有参数解析器那个支持解析这个参数

```java
	@Nullable
	private HandlerMethodArgumentResolver getArgumentResolver(MethodParameter parameter) {
		HandlerMethodArgumentResolver result = this.argumentResolverCache.get(parameter);
		if (result == null) {
			for (HandlerMethodArgumentResolver resolver : this.argumentResolvers) {
				if (resolver.supportsParameter(parameter)) {
					result = resolver;
					this.argumentResolverCache.put(parameter, result);//特别注意：之前判断该的就不用判断而是直接进入缓冲
					break;
				}
			}
		}
		return result;
	}
```

##### 5.2、解析这个参数的值

```java
调用各自 Handler（对应的方法）MethodArgumentResolver 的 resolveArgument 方法即可，其实这个resolveArgument是通过原生的Servelet来获取获得对应参数的值
```

怎么这么难？感觉我要死掉了

##### 5.3、自定义类型参数 封装POJO

我们进入以后我们经过判断循环后发现我们的的自定义的参数类型可以由**ServletModelAttributeMethodProcessor  这个参数处理器支持**

第一步我们通过isSimpleValueType要先判断我们的自定义类型 **是否为简单类型。**

```java
public static boolean isSimpleValueType(Class<?> type) {
		return (Void.class != type && void.class != type &&
				(ClassUtils.isPrimitiveOrWrapper(type) ||
				Enum.class.isAssignableFrom(type) ||
				CharSequence.class.isAssignableFrom(type) ||
				Number.class.isAssignableFrom(type) ||
				Date.class.isAssignableFrom(type) ||
				Temporal.class.isAssignableFrom(type) ||
				URI.class == type ||
				URL.class == type ||
				Locale.class == type ||
				Class.class == type));
	}
```



```java

@Override
	@Nullable
	public final Object resolveArgument(MethodParameter parameter, @Nullable ModelAndViewContainer mavContainer,
			NativeWebRequest webRequest, @Nullable WebDataBinderFactory binderFactory) throws Exception {

		Assert.state(mavContainer != null, "ModelAttributeMethodProcessor requires ModelAndViewContainer");
		Assert.state(binderFactory != null, "ModelAttributeMethodProcessor requires WebDataBinderFactory");

		String name = ModelFactory.getNameForParameter(parameter);
		ModelAttribute ann = parameter.getParameterAnnotation(ModelAttribute.class);
		if (ann != null) {
			mavContainer.setBinding(name, ann.binding());
		}

		Object attribute = null;
		BindingResult bindingResult = null;

		if (mavContainer.containsAttribute(name)) {
			attribute = mavContainer.getModel().get(name);
		}
		else {
			// Create attribute instance
			try {
				attribute = createAttribute(name, parameter, binderFactory, webRequest);
			}
			catch (BindException ex) {
				if (isBindExceptionRequired(parameter)) {
					// No BindingResult parameter -> fail with BindException
					throw ex;
				}
				// Otherwise, expose null/empty value and associated BindingResult
				if (parameter.getParameterType() == Optional.class) {
					attribute = Optional.empty();
				}
				bindingResult = ex.getBindingResult();
			}
		}

		if (bindingResult == null) {
			// Bean property binding and validation;
			// skipped in case of binding failure on construction.
			WebDataBinder binder = binderFactory.createBinder(webRequest, attribute, name);
			if (binder.getTarget() != null) {
				if (!mavContainer.isBindingDisabled(name)) {
					bindRequestParameters(binder, webRequest);  //开始绑定
				}
				validateIfApplicable(binder, parameter);
				if (binder.getBindingResult().hasErrors() && isBindExceptionRequired(binder, parameter)) {
					throw new BindException(binder.getBindingResult());
				}
			}
			// Value type adaptation, also covering java.util.Optional
			if (!parameter.getParameterType().isInstance(attribute)) {
				attribute = binder.convertIfNecessary(binder.getTarget(), parameter.getParameterType(), parameter);
			}
			bindingResult = binder.getBindingResult();
		}

		// Add resolved attribute and BindingResult at the end of the model
		Map<String, Object> bindingResultModel = bindingResult.getModel();
		mavContainer.removeAttributes(bindingResultModel);
		mavContainer.addAllAttributes(bindingResultModel);

		return attribute;
	}
```

1. 方法会帮我们创建一个空的对象

2. 在方法里面有一个`WebDataBinder binder = binderFactory.createBinder(webRequest, attribute, name);`方法，这里我们用我们的利用工厂绑定把数据。

   - **WebDataBinder** :web数据绑定器，将请求参数的值绑定到指定的JavaBean里面，**JavaBean就是我们的空对象**

   - 我们是使用HTTP超文本传输数据的，我们默认传的都是文本，此时我们需要WebDataBinder 利用它里面的 Converters 将请求数据转成指定的数据类型，再次封装到JavaBean中。

3. 下面我们介绍`GenericConversionService`方法，在设置每一个值的时候，找它里面的所有converter那个可以将这个数据类型（request带来参数的字符串）转换到指定的类型（JavaBean -- Integer），**把我们的byte转换成file流数据**

下面我们来可以看到对应的调取的转换方法

@FunctionalInterface**public interface** Converter<S, T>

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603337871521-25fc1aa1-133a-4ce0-a146-d565633d7658.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_39%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

这里简单展示我们的所有转换器



![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603338486441-9bbd22a9-813f-49bd-b51b-e66c7f4b8598.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_44%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



未来我们可以给WebDataBinder里面放自己的Converter；

我们用WebMvcConfigurer定制SpringMVC功能

**private static final class** StringToNumber<T **extends** Number> **implements** Converter<String, T>

自定义 Converter

```java
    //1、WebMvcConfigurer定制化SpringMVC的功能
    @Bean
    public WebMvcConfigurer webMvcConfigurer(){
        return new WebMvcConfigurer() {
            @Override
            public void addFormatters(FormatterRegistry registry) {
                //registry里面有addConverter方法
                registry.addConverter(new Converter<String, Pet>() {
				//把String转换成Pet
                    @Override
                    public Pet convert(String source) { //source是页面提交过来的值
                        // 即啊猫,3
                        if(!StringUtils.hasText(source)){//Spring的工具类
                            Pet pet = new Pet();
                            String[] split = source.split(",");
                            pet.setName(split[0]);
                            pet.setAge(Integer.parseInt(split[1]));
                            return pet;
                        }
                        return null;
                    }
                });
            }
        };
    }
```

#### 6、目标方法执行完成

将所有的数据都放在 **ModelAndViewContainer**；包含要去的页面地址View。还包含Model数据。

![image.png](https://cdn.nlark.com/yuque/0/2020/png/1354552/1603272018605-1bce3142-bdd9-4834-a028-c753e91c52ac.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_16%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

#### 7、处理派发结果 

在目标方法执行完成，得到对应的数据，此时我们要处理结果

**processDispatchResult**(processedRequest, response, mappedHandler, mv, dispatchException);



renderMergedOutputModel(mergedModel, getRequestToExpose(request), response);

- mergedModel里面是我们的数据
- getRequestToExpose(request)拿到请求对象，获取到原生的servletrequest对象
- response是我们的要回复的东西

下面我们来了解`renderMergedOutputModel`原理

```java
InternalResourceView：
@Override
  protected void renderMergedOutputModel(
      Map<String, Object> model, HttpServletRequest request, HttpServletResponse response) throws Exception {

    // Expose the model object as request attributes.
    exposeModelAsRequestAttributes(model, request);   //我们重点要了解的方法

    // Expose helpers as request attributes, if any.
    exposeHelpers(request);

    // Determine the path for the request dispatcher.
    String dispatcherPath = prepareForRendering(request, response);

    // Obtain a RequestDispatcher for the target resource (typically a JSP).
    RequestDispatcher rd = getRequestDispatcher(request, dispatcherPath);
    if (rd == null) {
      throw new ServletException("Could not get RequestDispatcher for [" + getUrl() +
          "]: Check that the corresponding file exists within your web application archive!");
    }

    // If already included or response already committed, perform include, else forward.
    if (useInclude(request, response)) {
      response.setContentType(getContentType());
      if (logger.isDebugEnabled()) {
        logger.debug("Including [" + getUrl() + "]");
      }
      rd.include(request, response);
    }

    else {
      // Note: The forwarded resource is supposed to determine the content type itself.
      if (logger.isDebugEnabled()) {
        logger.debug("Forwarding to [" + getUrl() + "]");
      }
      rd.forward(request, response);
    }
  }
```

在这个`renderMergedOutputModel`里面有一个特别重要的方法，我们查看对应的`exposeModelAsRequestAttributes`的源码

```java
暴露模型作为请求域属性
// Expose the model object as request attributes.
		exposeModelAsRequestAttributes(model, request);
```

```java
protected void exposeModelAsRequestAttributes(Map<String, Object> model,
			HttpServletRequest request) throws Exception {

    //model中的所有数据遍历挨个放在请求域中，这就是为什么我们的Map和Model最后会被放在请求域当中
		model.forEach((name, value) -> {
			if (value != null) {
				request.setAttribute(name, value);  //设置对应的kv值
			}
			else {
				request.removeAttribute(name);
			}
		});
	}
```

## 2.4 数据响应与内容协商

![image-20211008083200371](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211008083200371.png)

#### 2.4.1 响应JSON



##### 1、jackson.jar和@ResponseBody

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-json</artifactId>
    <version>2.3.4.RELEASE</version>
    <scope>compile</scope>
</dependency>
```

给前端自动返回json数据；

###### 1.1 返回值解析器

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605151359370-01cd1fbe-628a-4eea-9430-d79a78f59125.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_25%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

1.得到返回值类型`getReturnValueType(returnValue)`

```java
try {
			this.returnValueHandlers.handleReturnValue(
					returnValue, getReturnValueType(returnValue), mavContainer, webRequest);
		}
```

2.处理返回值`handleReturnValue`

```java
	@Override
	public void handleReturnValue(@Nullable Object returnValue, MethodParameter returnType,
			ModelAndViewContainer mavContainer, NativeWebRequest webRequest) throws Exception {

		HandlerMethodReturnValueHandler handler = selectHandler(returnValue, returnType); //找能处理返回值的处理器
		if (handler == null) {
			throw new IllegalArgumentException("Unknown return value type: " + returnType.getParameterType().getName());//找不到抛出异常
		}
		handler.handleReturnValue(returnValue, returnType, mavContainer, webRequest); //找到则拿处理器处理返回值
	}
```

3.处理器的`handleReturnValue`的方法

```java
RequestResponseBodyMethodProcessor  	
@Override
	public void handleReturnValue(@Nullable Object returnValue, MethodParameter returnType,
			ModelAndViewContainer mavContainer, NativeWebRequest webRequest)
			throws IOException, HttpMediaTypeNotAcceptableException, HttpMessageNotWritableException {

		mavContainer.setRequestHandled(true);
		ServletServerHttpRequest inputMessage = createInputMessage(webRequest);
		ServletServerHttpResponse outputMessage = createOutputMessage(webRequest);

		// Try even with null return value. ResponseBodyAdvice could get involved.
        // 使用消息转换器进行写出操作
		writeWithMessageConverters(returnValue, returnType, inputMessage, outputMessage);
	}
```



###### 1.2 返回值解析器原理

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605151728659-68c8ce8a-1b2b-4ab0-b86d-c3a875184672.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_23%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

- 1、返回值处理器判断是否支持这种类型返回值 `supportsReturnType`
- 2、返回值处理器调用 `handleReturnValue` 进行处理

- 3、`RequestResponseBodyMethodProcessor `可以处理返回值标了`@ResponseBody `注解的。

- - 1.利用 `MessageConverters `进行处理 将数据写为json

- - - 1、内容协商（浏览器默认会以请求头的方式告诉服务器他能接受什么样的内容类型）

    - 2、服务器最终根据自己自身的能力，决定服务器能生产出什么样内容类型的数据，决定我们要用数据类型

      > 在SpringMvc中，我们在内部得到浏览器能接受的类型和服务器能生产的类型。服务器和浏览器开始匹配看浏览器能不能接收，匹配成功时候，我们会给`mediaTypeToUse`赋值，表明我们能写什么样的数据

- - - 3、SpringMVC会挨个遍历所有容器底层的 `HttpMessageConverter` ，看谁能处理？

      > 每一个`HttpMessageConverter` 都有一个`canRead`和`canWrite`，两个都是boolean类型的来看支不支持把我们的对象写进去，读出来

- - - - 1、得到`MappingJackson2HttpMessageConverter`可以将对象写为json
      - 2、利用MappingJackson2HttpMessageConverter将**对象转为json**再写出去。

##### 2、SpringMVC到底支持哪些返回值

```java
ModelAndView
Model
View
ResponseEntity 
ResponseBodyEmitter
StreamingResponseBody
HttpEntity
HttpHeaders
Callable
DeferredResult
ListenableFuture
CompletionStage
WebAsyncTask
有 @ModelAttribute 且为对象类型的
@ResponseBody 注解 ---> RequestResponseBodyMethodProcessor；
```

##### 3、HTTPMessageConverter原理

###### 1、MessageConverter规范

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605163447900-e2748217-0f31-4abb-9cce-546b4d790d0b.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_19%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

`HttpMessageConverter`看是否支持将此 Class类型的对象，转为`MediaType`类型的数据。

例子：Person对象转为JSON。或者 JSON转为Person



###### 2、默认的MessageConverter

下面介绍我们的默认转换器

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605163584708-e19770d6-6b35-4caa-bf21-266b73cb1ef1.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_17%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

要判断我们支持返回值类型

```java
0 - 只支持Byte类型的

1 - String

2 - String

3 - Resource

4 - ResourceRegion

5 - DOMSource.class \ SAXSource.class \ StAXSource.class StreamSource.class \Source.class

6 - MultiValueMap

7 - true

8 - true

9 - 支持注解方式xml处理的。
```



**最终 MappingJackson2HttpMessageConverter  把对象转为JSON（利用底层的jackson的objectMapper转换的），如图所示**

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605164243168-1a31e9af-54a4-463e-b65a-c28ca7a8a2fa.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_34%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

#### 2.4.2 内容协商

根据客户端接收能力不同，返回不同媒体类型的数据。

##### 1、引入xml依赖

```xml
<dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-xml</artifactId>
</dependency>
```

##### 2、postman分别测试返回json和xml

只需要改变请求头中Accept字段。Http协议中规定的，告诉服务器本客户端可以接收的数据类型。

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605173127653-8a06cd0f-b8e1-4e22-9728-069b942eba3f.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_33%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



##### 3、开启浏览器参数方式内容协商功能

为了方便内容协商，开启基于请求参数的内容协商功能。当我们请求带了`format`参数，我们可以指定我们的要返回什么样的内容

```yaml
spring:
    contentnegotiation:
      favor-parameter: true  #开启请求参数内容协商模式
```

发请求： http://localhost:8080/test/person?format=json

[http://localhost:8080/test/person?format=](http://localhost:8080/test/person?format=json)xml

此时，我们的`strategies`会有一个专门的`ParametercontentNegotiationStrategy` 参数名字就叫format，支持我们可以写xml/json



![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605230907471-b0ed34bc-6782-40e7-84b7-615726312f01.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_22%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

>    public List<MediaType> resolveMediaTypes(NativeWebRequest webRequest) throws HttpMediaTypeNotAcceptableException {
>          return this.resolveMediaTypeKey(webRequest, this.getMediaTypeKey(webRequest)); 
>      }



确定客户端接收什么样的内容类型；

1、Parameter策略优先确定是要返回json数据（获取请求头中的format的值）

>protected String getMediaTypeKey(NativeWebRequest request){
>
>return request.getParameter(getParameterName());//getParameterName()即format
>
>}

2、最终进行内容协商返回给客户端json即可。

##### 4、内容协商原理

一个URL的资源服务端可以有多种响应形式，即MIME（Media Type）媒体类型。但客户端只需要一种，这就要求客户端和服务端之间有一种机制，能确保服务端响应的是客户端想要的，这就是内容协商。

客户端发送请求时指明需要的MIME，比如HTTP首部的Accept；服务端根据客户端的要求返回对应的内容形式，并在响应头中说明，比如Content-Type。详见下表：

| 请求头          | 请求头说明               | 响应头           | 响应头说明               |
| --------------- | ------------------------ | ---------------- | ------------------------ |
| Accept          | 告诉服务端需要的MIME     | Content-Type     | 告诉客户端响应的媒体类型 |
| Accept-Language | 告诉服务端需要的语言     | Content-Language | 告诉客户端响应的语言     |
| Accept-Charset  | 告诉服务端需要的字符集   | Content-Charset  | 告诉客户端响应的字符集   |
| Accept-Encoding | 告诉服务端需要的压缩方式 | Content-Encoding | 告诉客户端响应的压缩方式 |

下面我们来看请求头

![img](https://img2018.cnblogs.com/blog/182350/201907/182350-20190727232316657-995550301.png)

首先解释一下q，权重的意思，最高为1，最低为0，默认是1。

Accept：*/*表示可以是任何MIME资源，其他的比如text/plain，text/html等。

Accept-Encoding：压缩方式可以是gzip,deflate,br。服务端向客户端发送的资源可通过压缩减少传输量。

Accept-Language：中文的权重最高。这里浏览器可以根据操作系统的语言或者浏览器本身的语言设置来选择，但能否协商成功还要看服务端是否支持多语言。

再看个响应首部的例子：

![img](https://img2018.cnblogs.com/blog/182350/201907/182350-20190727232525421-926226730.png)

Content-Encoding：说明压缩的方式是gzip。

Content-Type：表示MIME是html文本，字符集是utf-8



**Spring MVC的内容协商**

- 1、判断当前响应头中是否已经有确定的媒体类型。MediaType

  >MediaType contentType =outputMessage.getHeader().getContentType();

- **2、获取客户端（PostMan、浏览器）支持接收的内容类型。（获取客户端Accept请求头字段）**

  > List<MediaType> acceptableTypes = getAcceptableTypes(request);

- - **利用我们的contentNegotiationManager（内容协商管理器 ）的`resolveMediaTypes`方法来获取媒体类型，里面有个`strategies`即默认使用基于请求头的策略**

    > private List<MediaType> getAcceptableTypes(HttpServletRequest request) throws HttpMediaTypeNotAcceptableException{
    >
    > return this.contentNegotiationManager.resolveMediaTypes(new ServletWebRequest(request));
    >
    > }

    > public ServletWebRequest(HttpServlet request){
    >
    > super(request);
    >
    > }

  - ![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605230462280-ef98de47-6717-4e27-b4ec-3eb0690b55d0.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_15%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

- - **`HeaderContentNegotiationStrategy`是继承`ContentNegotiationStrategy ` 基于请求头的内容协商策列，来确定客户端可以接收的内容类型** ，下面是`HeaderContentNegotiationStrategy`的源码，我们可以看到，**本质上就是用原生的`request.getHeaderValues(Http.ACCEPT);`**来获取我们的请求头来确定我们的可以接受内容类型，返回为`headerValueArray`数组
  - ![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605230546376-65dcf657-7653-4a58-837a-f5657778201a.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_28%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

- 3、遍历循环所有当前系统的 **MessageConverter**，看谁支持操作这个对象（Person）

  >    List mediaTypes;
  >         do {
  >             if (!var2.hasNext()) {
  >                 return MEDIA_TYPE_ALL_LIST; // */*
  >             }
  >             ContentNegotiationStrategy strategy = (ContentNegotiationStrategy)var2.next();
  >             mediaTypes = strategy.resolveMediaTypes(request); //重点是这个
  >         } while(mediaTypes.equals(MEDIA_TYPE_ALL_LIST));
  >
  >     return mediaTypes; //得到即返回，不然还是模糊匹配

- 4、找到支持操作Person的converter，把converter支持的媒体类型统计出来。

  > 找到converter获取它支持的媒体类型，相当于我们要得到我们的converter到底能支持哪些数据，相当于我们系统的底层能力

- 5、客户端需要【application/xml】。服务端能力【10种、json、xml】

-   ![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605173876646-f63575e2-50c8-44d5-9603-c2d11a78adae.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_20%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

- 6、进行内容协商的最佳匹配媒体类型

- 7、用 支持 将对象转为 最佳匹配媒体类型 的converter。调用它进行转化 。

  > 前面找谁能读入，后面找谁能输出





![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605173657818-73331882-6086-490c-973b-af46ccf07b32.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_18%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

导入了jackson处理xml的包，xml的converter就会自动进来

```java
WebMvcConfigurationSupport
jackson2XmlPresent = ClassUtils.isPresent("com.fasterxml.jackson.dataformat.xml.XmlMapper", classLoader);

if (jackson2XmlPresent) {
			Jackson2ObjectMapperBuilder builder = Jackson2ObjectMapperBuilder.xml();
			if (this.applicationContext != null) {
				builder.applicationContext(this.applicationContext);
			}
			messageConverters.add(new MappingJackson2XmlHttpMessageConverter(builder.build()));
		}
```







##### 5、自定义 MessageConverter

**实现多协议数据兼容。json、xml、x-guigu**

**0、**@ResponseBody 响应数据出去 调用 **RequestResponseBodyMethodProcessor** 处理

1、Processor 处理方法返回值。通过 **MessageConverter** 处理

2、所有 **MessageConverter** 合起来可以支持各种媒体类型数据的操作（读、写）

3、内容协商找到最终的 **messageConverter**；



SpringMVC的什么功能。一个入口给容器中添加一个  WebMvcConfigurer

```java
 @Bean
    public WebMvcConfigurer webMvcConfigurer(){
        return new WebMvcConfigurer() {

            @Override
            public void extendMessageConverters(List<HttpMessageConverter<?>> converters) {
					converters.add(new CeitMessageConverter());//添加自己的converter
            }
        }
    }
```

```java
//自己的实现的converter建议新建一个converter文件夹
//假如我们有对应协议application/x-ceit
public class CeitMessageConverter implements HttpMessageConverter<Person> {  //关于
    @Override
    public List<MediaType> getSupportedMediaTypes(Class<?> clazz) {
        return null;
    }

    @Override
    public boolean canRead(Class<?> clazz, MediaType mediaType) {
        return false;
    }

    @Override
    public boolean canWrite(Class<?> clazz, MediaType mediaType) {
        return clazz.isAssignableFrom(Person.class);  //只要是person就可以读写
    }

    @Override
    public List<MediaType> getSupportedMediaTypes() {  //服务器要统计所有的MessageConverter能写的内容
        // 这里要告诉SprinMvc我们的MessageConverter能干嘛
        //我们这能操作application/x-ceit类型
        return MediaType.parseMediaTypes("application/x-ceit");
    }

    @Override
    public Person read(Class<? extends Person> clazz, HttpInputMessage inputMessage) throws IOException, HttpMessageNotReadableException {
        return null;
    }

    @Override
    public void write(Person person, MediaType contentType, HttpOutputMessage outputMessage) throws IOException, HttpMessageNotWritableException {
        //自定义我们数据的写出
        String data =person.getName()+" "+person.getAge();
        //写出去,输出流
        OutputStream body = outputMessage.getBody();
        //转成byte来放进去
        body.write(data.getBytes(data));
    }
}
```





![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605260623995-8b1f7cec-9713-4f94-9cf1-8dbc496bd245.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_18%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



如何实现我们兼容我们的自定义的值

```java
   @Bean
    public WebMvcConfigurer webMvcConfigurer(){
        return new WebMvcConfigurer() {
            @Override
            public void configureContentNegotiation(ContentNegotiationConfigurer configurer) {

                Map<String, MediaType> mediaTypes = new HashMap<>();
                mediaTypes.put("json",MediaType.APPLICATION_JSON);
                mediaTypes.put("xml",MediaType.APPLICATION_XML);
                mediaTypes.put("gg",MediaType.parseMediaType("application/x-ceit"));
                //指定支持解析哪些参数对应的媒体类型
                ParameterContentNegotiationStrategy strategy = new ParameterContentNegotiationStrategy(mediaTypes);

                configurer.strategies(Arrays.asList(strategy));
            }
        };
    }
```

此时我们有三种匹配的值

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605261062877-0a27cc41-51cb-4018-a9af-4e0338a247cd.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_27%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

我们这时候只有参数的没有请求头的，此时我们就相当于请求头*/* ，此时我们基于请求头都失效，无论返回什么都是json数据

```java
HeaderContentNegotiationStrategy headerStrategy = new HeaderContentNegotiationStrategy();
//写请求头，除此之外我们还可以自己编写其他的策略
configurer.strategies(Arrays.asList(strategy,headerStrategy));
```



**有可能我们添加的自定义的功能会覆盖默认很多功能，导致一些默认的功能失效。**

**大家考虑，上述功能除了我们完全自定义外？SpringBoot有没有为我们提供基于配置文件的快速修改媒体类型功能？怎么配置呢？【提示：参照SpringBoot官方文档web开发内容协商章节】**

## 2.5 视图解析与模板引擎

视图解析：**SpringBoot默认不支持 JSP，需要引入第三方模板引擎技术实现页面渲染。**

### 2.5.1、视图解析

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1606043749039-cefbf687-4feb-441d-bad8-c6d933248d3c.png)

#### 1、视图解析原理流程

1、目标方法处理的过程中，所有数据都会被放在 **ModelAndViewContainer 里面。包括数据和视图地址**

**2、方法的参数是一个自定义类型对象（从请求参数中确定的），把他重新放在ModelAndViewContainer** 

**3、任何目标方法执行完成以后都会返回 ModelAndView（数据和视图地址）。**

**4、processDispatchResult  处理派发结果（页面改如何响应）**

- 1、**render**(**mv**, request, response); 进行页面渲染逻辑

- - 1、根据方法的String返回值得到 **View** 对象【定义了页面的渲染逻辑】

- - - 1、所有的视图解析器尝试是否能根据当前返回值得到**View**对象
    - 2、得到了  **redirect:/main.html** --> Thymeleaf new **RedirectView**()

- - - 3、ContentNegotiationViewResolver 里面包含了下面所有的视图解析器，内部还是利用下面所有视图解析器得到视图对象。
    - 4、view.render(mv.getModelInternal(), request, response);   视图对象调用自定义的render进行页面渲染工作

- - - - **RedirectView 如何渲染【重定向到一个页面】**
      - **1、获取目标url地址**

- - - - **2、response.sendRedirect(encodedURL);**





**视图解析：**

- - **返回值以 forward: 开始： new InternalResourceView(forwardUrl); -->  转发****request.getRequestDispatcher(path).forward(request, response);** 
  - **返回值以** **redirect: 开始：** **new RedirectView() --》 render就是重定向** 

- - **返回值是普通字符串： new ThymeleafView（）--->** 





自定义视图解析器+自定义视图； 









![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605680247945-088b0f17-185c-490b-8889-103e8b4d8c07.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_16%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605679959020-54b96fe7-f2fc-4b4d-a392-426e1d5413de.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_23%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605679471537-7db702dc-b165-4dc6-b64a-26459ee5fd6c.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_17%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605679913592-151a616a-c754-4da3-a2c1-91dc0230a48d.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_22%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

### 2.5.2 模板引擎-Thymeleaf

#### 1、thymeleaf简介

Thymeleaf is a modern server-side Java template engine for both web and standalone environments, capable of processing HTML, XML, JavaScript, CSS and even plain text.

**现代化、服务端Java模板引擎**



### 2.5.3 Thymeleaf基本语法

#### 1、表达式

| 表达式名字 | 语法   | 用途                               |
| ---------- | ------ | ---------------------------------- |
| 变量取值   | ${...} | 获取请求域、session域、对象等值    |
| 选择变量   | *{...} | 获取上下文对象值                   |
| 消息       | #{...} | 获取国际化等值                     |
| 链接       | @{...} | 生成链接                           |
| 片段表达式 | ~{...} | jsp:include 作用，引入公共页面片段 |



#### 2、字面量

文本值: **'one text'** **,** **'Another one!'** **,…**

数字: **0** **,** **34** **,** **3.0** **,** **12.3** **,…**

布尔值: **true** **,** **false**

空值: **null**

变量： one，two，.... 变量不能有空格

#### 3、文本操作

字符串拼接: **+**

变量替换: **|The name is ${name}|** 



#### 4、数学运算

运算符: + , - , * , / , %



#### 5、布尔运算

运算符:  **and** **,** **or**

一元运算: **!** **,** **not** 





#### 6、比较运算

比较: **>** **,** **<** **,** **>=** **,** **<=** **(** **gt** **,** **lt** **,** **ge** **,** **le** **)**等式: **==** **,** **!=** **(** **eq** **,** **ne** **)** 



#### 7、条件运算

If-then: **(if) ? (then)**

If-then-else: **(if) ? (then) : (else)**

Default: (value) **?: (defaultvalue)** 



#### 8、特殊操作

无操作： _





### 2.5.4 设置属性值-th:attr

设置单个值

```html
<form action="subscribe.html" th:attr="action=@{/subscribe}">
  <fieldset>
    <input type="text" name="email" />
    <input type="submit" value="Subscribe!" th:attr="value=#{subscribe.submit}"/>
  </fieldset>
</form>
```

设置多个值

```html
<img src="../../images/gtvglogo.png"  th:attr="src=@{/images/gtvglogo.png},title=#{logo},alt=#{logo}" />
```



以上两个的代替写法 th:xxxx

```html
<input type="submit" value="Subscribe!" th:value="#{subscribe.submit}"/>
<form action="subscribe.html" th:action="@{/subscribe}">
```



所有h5兼容的标签写法

https://www.thymeleaf.org/doc/tutorials/3.0/usingthymeleaf.html#setting-value-to-specific-attributes



### 2.5.5 迭代

```html
<tr th:each="prod : ${prods}">
        <td th:text="${prod.name}">Onions</td>
        <td th:text="${prod.price}">2.41</td>
        <td th:text="${prod.inStock}? #{true} : #{false}">yes</td>
</tr>
```



```html
<tr th:each="prod,iterStat : ${prods}" th:class="${iterStat.odd}? 'odd'">
  <td th:text="${prod.name}">Onions</td>
  <td th:text="${prod.price}">2.41</td>
  <td th:text="${prod.inStock}? #{true} : #{false}">yes</td>
</tr>
```



### 2.5.6 条件运算

```html
<a href="comments.html"
th:href="@{/product/comments(prodId=${prod.id})}"
th:if="${not #lists.isEmpty(prod.comments)}">view</a>
```



```html
<div th:switch="${user.role}">
  <p th:case="'admin'">User is an administrator</p>
  <p th:case="#{roles.manager}">User is a manager</p>
  <p th:case="*">User is some other thing</p>
</div>
```



### 2.5.7 属性优先级

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605498132699-4fae6085-a207-456c-89fa-e571ff1663da.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_44%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

### 2.5.8 thymeleaf使用

#### 1、引入Starter

```java
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

#### 2、自动配置好了thymeleaf

ThymeleafAutoConfiguration自动配置

```java
@Configuration(proxyBeanMethods = false)
@EnableConfigurationProperties(ThymeleafProperties.class)
@ConditionalOnClass({ TemplateMode.class, SpringTemplateEngine.class })
@AutoConfigureAfter({ WebMvcAutoConfiguration.class, WebFluxAutoConfiguration.class })
public class ThymeleafAutoConfiguration { }
```



自动配好的策略

- 1、所有thymeleaf的配置值都在 ThymeleafProperties
- 2、配置好了 **SpringTemplateEngine** 

- 3、配好了 **ThymeleafViewResolver** 即视图解析器
- 4、我们只需要直接开发页面

下面是我们对应的视图解析器

```java
	public static final String DEFAULT_PREFIX = "classpath:/templates/";

	public static final String DEFAULT_SUFFIX = ".html";  //默认跳转xxx.html
```

#### 3、页面开发

每个页面开发我们需要加一个模板

```java
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h1 th:text="${msg}"></h1>
<h2>
    <a href="www.ceit.com" th:href="${link}">去百度01</a>
    <a href="www.ceit.com" th:href="@{link}">去百度02</a>
</h2>
</body>
</html>
```

对应的Controller

```java
@Controller
public class ViewTestController {
    @GetMapping("/ceit")
    public String ceit(Model model){
        model.addAttribute("msg","你好，ceit");
        model.addAttribute("link","http://www.baidu.com");
        return "success";
    }
}
```



## 4、构建后台管理系统

### 1、项目创建

thymeleaf、web-starter、devtools、lombok



### 2、静态资源处理

自动配置好，我们只需要把所有静态资源放到 static 文件夹下

### 3、路径构建

th:action="@{/login}"



### 4、模板抽取

th:insert/replace/include



### 5、页面跳转

```java
    @PostMapping("/login")
    public String main(User user, HttpSession session, Model model){

        if(StringUtils.hasLength(user.getUserName()) && "123456".equals(user.getPassword())){
            //把登陆成功的用户保存起来
            session.setAttribute("loginUser",user);
            //登录成功重定向到main.html;  重定向防止表单重复提交
            return "redirect:/main.html";
        }else {
            model.addAttribute("msg","账号密码错误");
            //回到登录页面
            return "login";
        }

    }
```



### 6、数据渲染

```java
    @GetMapping("/dynamic_table")
    public String dynamic_table(Model model){
        //表格内容的遍历
        List<User> users = Arrays.asList(new User("zhangsan", "123456"),
                new User("lisi", "123444"),
                new User("haha", "aaaaa"),
                new User("hehe ", "aaddd"));
        model.addAttribute("users",users);

        return "table/dynamic_table";
    }
        <table class="display table table-bordered" id="hidden-table-info">
        <thead>
        <tr>
            <th>#</th>
            <th>用户名</th>
            <th>密码</th>
        </tr>
        </thead>
        <tbody>
        <tr class="gradeX" th:each="user,stats:${users}">
            <td th:text="${stats.count}">Trident</td>
            <td th:text="${user.userName}">Internet</td>
            <td >[[${user.password}]]</td>
        </tr>
        </tbody>
        </table>
```



## 6、拦截器

## 1、HandlerInterceptor 接口

```java
/**
 * 登录检查
 * 1、配置好拦截器要拦截哪些请求
 * 2、把这些配置放在容器中
 */
@Slf4j
public class LoginInterceptor implements HandlerInterceptor {

    /**
     * 目标方法执行之前
     * @param request
     * @param response
     * @param handler
     * @return
     * @throws Exception
     */
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {

        String requestURI = request.getRequestURI();
        log.info("preHandle拦截的请求路径是{}",requestURI);

        //登录检查逻辑
        HttpSession session = request.getSession();

        Object loginUser = session.getAttribute("loginUser");

        if(loginUser != null){
            //放行
            return true;
        }

        //拦截住。未登录。跳转到登录页
        request.setAttribute("msg","请先登录");
//        re.sendRedirect("/");
        request.getRequestDispatcher("/").forward(request,response);
        return false;
    }

    /**
     * 目标方法执行完成以后
     * @param request
     * @param response
     * @param handler
     * @param modelAndView
     * @throws Exception
     */
    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        log.info("postHandle执行{}",modelAndView);
    }

    /**
     * 页面渲染以后
     * @param request
     * @param response
     * @param handler
     * @param ex
     * @throws Exception
     */
    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        log.info("afterCompletion执行异常{}",ex);
    }
}
```



## 2、配置拦截器

```java
/**
 * 1、编写一个拦截器实现HandlerInterceptor接口
 * 2、拦截器注册到容器中（实现WebMvcConfigurer的addInterceptors）
 * 3、指定拦截规则【如果是拦截所有，静态资源也会被拦截】
 */
@Configuration
public class AdminWebConfig implements WebMvcConfigurer {

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(new LoginInterceptor())
                .addPathPatterns("/**")  //所有请求都被拦截包括静态资源
                .excludePathPatterns("/","/login","/css/**","/fonts/**","/images/**","/js/**"); //放行的请求
    }
}
```



## 3、拦截器原理

1、根据当前请求，找到`HandlerExecutionChain`,即可以处理请求的handler以及handler的所有拦截器

2、先来**顺序执行** 所有拦截器的 preHandle方法

- 1、如果当前拦截器prehandler返回为true。则执行下一个拦截器的preHandle
- 2、如果当前拦截器返回为false。直接倒序执行所有已经执行了的拦截器的afterCompletion；

**3、如果任何一个拦截器返回false。直接跳出不执行目标方法**

**4、所有拦截器都返回True。执行目标方法**

**5、倒序执行所有拦截器的postHandle方法。**

**6、前面的步骤有任何异常都会直接倒序触发** afterCompletion

7、页面成功渲染完成以后，也会倒序触发 afterCompletion



![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605764129365-5b31a748-1541-4bee-9692-1917b3364bc6.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_44%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605765121071-64cfc649-4892-49a3-ac08-88b52fb4286f.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_35%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

# 3、数据访问

在Springboot进行数据访问

![image-20211009213732131](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211009213732131.png)

我们可以知道我们只需要进行场景的引入和编写对应的配置项即可。

## 3.1、数据源的自动配置

### 3.1.1、导入JDBC场景

引入对应的依赖

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-jdbc</artifactId>
        </dependency>
```

### 3.1.2、分析自动配置

我们来了解它做了什么自动的配置，才能知道去哪配置

我们点击我们的Ctrl+`spring-boot-starter-data-jdbc`

```xml
  <dependencies>
    <dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-starter-jdbc</artifactId>
      <version>2.5.5</version>
      <scope>compile</scope>
    </dependency>
    <dependency>
      <groupId>org.springframework.data</groupId>
      <artifactId>spring-data-jdbc</artifactId>
      <version>2.2.5</version>
      <scope>compile</scope>
    </dependency>
  </dependencies>
```

- `spring-data-jdbc`来进行jdbc数据操作
- `spring-boot-starter-jdbc`进入以后我们查看对应的依赖

```xml
  <dependencies>
    <dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-starter</artifactId>
      <version>2.5.5</version>
      <scope>compile</scope>
    </dependency>
    <dependency>
      <groupId>com.zaxxer</groupId>
      <artifactId>HikariCP</artifactId>
      <version>4.0.3</version>
      <scope>compile</scope>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-jdbc</artifactId>
      <version>5.3.10</version>
      <scope>compile</scope>
    </dependency>
  </dependencies>
```

- `HikariCP`是数据库连接池

综上所述，我们导入了事务的支持，对应的jdbc和数据源，但是，官方不知道我们接下要操作什么数据库，我们缺少我们的数据库驱动。

我们接下来要用什么数据库就要导入什么驱动，而且是**数据库版本和驱动版本对应**的驱动。

> 官方里面做了对应的mysql的驱动，但是要是我们的数据库版本和驱动不匹配的情况下，数据库操作会出现错误

如何查看自己的数据库版本呢

```cmd
mysql -V
mysql  Ver 8.0.23 for Win64 on x86_64 (MySQL Community Server - GPL)
```

我的数据库版本是8.0.23，所有对应也应该是

```xml
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.23</version>
        </dependency>
```

这是利用Maven的就近依赖原则，也可以修改properties里面重新声明对应的mysql版本（Maven的属性的就近优先原则）

```xml
    <properties>
        <java.version>1.8</java.version>
        <mysql.version>8.0.23</mysql.version>
    </properties>
```

我们来了解它帮我们自动配置了什么

#### 1、自动配置的类

我们进入对应的自动配置类找到我们对应的jdbc，点击进去查看，下面我们看到几个重要的东西

- `DataSourceAutoConfiguration`:数据源的自动配置

```java
@Configuration(
    proxyBeanMethods = false
)
@ConditionalOnClass({DataSource.class, EmbeddedDatabaseType.class})
@ConditionalOnMissingBean(
    type = {"io.r2dbc.spi.ConnectionFactory"}
)//基于响应式编程的
@EnableConfigurationProperties({DataSourceProperties.class})//开启配置文件绑定功能
@Import({DataSourcePoolMetadataProvidersConfiguration.class, InitializationSpecificCredentialsDataSourceInitializationConfiguration.class, SharedCredentialsDataSourceInitializationConfiguration.class})
public class DataSourceAutoConfiguration {}
```

查看`DataSourceProperties.class`

```java
@ConfigurationProperties(
    prefix = "spring.datasource" 
)//重点
public class DataSourceProperties implements BeanClassLoaderAware, InitializingBean {}
```

即我们要修改数据源配置则在配置文件中修改**`spring.datasource`**开头的信息就好，然后看到方法

```java
    @Configuration(
        proxyBeanMethods = false
    )
    @Conditional({DataSourceAutoConfiguration.PooledDataSourceCondition.class})
    @ConditionalOnMissingBean({DataSource.class, XADataSource.class})//重点
    @Import({Hikari.class, Tomcat.class, Dbcp2.class, OracleUcp.class, Generic.class, DataSourceJmxConfiguration.class})
    protected static class PooledDataSourceConfiguration {
        protected PooledDataSourceConfiguration() {
        }
    }
```

即自己没有数据库连接池的时候我们才进行自动配置，用`import`导入一堆相关类，但我们在引入场景时候已经引入了数据源



- `DataSourceTransactionManagerAutoConfiguration`:事务管理器的自动配置
- `JdbcTemplateAutoConfiguration`:jdbc组件的自动配置，因为我们没有整合任何第三方方框，这是Spring官方给我们的一个可以增删改查操作

```java
@Configuration(
    proxyBeanMethods = false
)
@ConditionalOnClass({DataSource.class, JdbcTemplate.class})
@ConditionalOnSingleCandidate(DataSource.class)
@AutoConfigureAfter({DataSourceAutoConfiguration.class})
@EnableConfigurationProperties({JdbcProperties.class})//重点
@Import({DatabaseInitializationDependencyConfigurer.class, JdbcTemplateConfiguration.class, NamedParameterJdbcTemplateConfiguration.class})//重点
public class JdbcTemplateAutoConfiguration {
    public JdbcTemplateAutoConfiguration() {
    }
}
```

我们查看对应的`JdbcProperties.class`

```java
@ConfigurationProperties(
    prefix = "spring.jdbc"
)
public class JdbcProperties {}
```

即我们要修改数据源配置则在配置文件中修改**`spring.jdbc`**开头的信息就好

再看`JdbcTemplateConfiguration.class`

```java
@ConditionalOnMissingBean({JdbcOperations.class})
class JdbcTemplateConfiguration {
    JdbcTemplateConfiguration() {
    }

    @Bean
    @Primary
    JdbcTemplate jdbcTemplate(DataSource dataSource, JdbcProperties properties) {
        JdbcTemplate jdbcTemplate = new JdbcTemplate(dataSource);
        Template template = properties.getTemplate();
        jdbcTemplate.setFetchSize(template.getFetchSize());
        jdbcTemplate.setMaxRows(template.getMaxRows());
        if (template.getQueryTimeout() != null) {
            jdbcTemplate.setQueryTimeout((int)template.getQueryTimeout().getSeconds());
        }

        return jdbcTemplate;
    }
}
```

这个类返回了`jdbcTemplate`对象了

- `JndiDataSourceAutoConfiguration`:jndi的自动配置
- `XADataSourceAutoConfiguration`:分布式事务相关的

### 3.1.3、修改配置项

创建我们的application.yaml文件，要写对应的数据库驱动

```yaml
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/ssm_crud?useSSL=false&serverTimezone=UTC
    username: root
    password: 123456
    driver-class-name: com.mysql.cj.jdbc.Driver
```

### 3.1.4、测试

下面，我们将进行数据库进行测试

1. 对应的测试代码

```java
@Slf4j
@SpringBootTest
class BootWebAdminApplicationTests {
    @Autowired
    JdbcTemplate jdbcTemplate;

    @Test
    void contextLoads() {
        Long aLong = jdbcTemplate.queryForObject("select count(*) from tbl_emp", Long.class);
        log.info("记录总数为{}",aLong);
    }

}
```

2. 对应的结果

![image-20211009224500671](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211009224500671.png)

## 3.2、使用Druid数据源

### 3.2.1、druid官方网址

https://github.com/alibaba/druid



整合第三方技术的两种方式

- 自定义
- 找starter

```xml
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid</artifactId>
            <version>1.1.22</version>
        </dependency>
```



### 3.2.2、自定义方式

> 复杂且不推荐，是用来复习之前配置里面如何在SpringBoot里面进行编写

在`DataSourceJmxConfiguration`中有

```java
    @Configuration(
        proxyBeanMethods = false
    )
    @ConditionalOnClass({HikariDataSource.class})
    @ConditionalOnMissingBean({DataSource.class})
    @ConditionalOnProperty(
        name = {"spring.datasource.type"},
        havingValue = "com.zaxxer.hikari.HikariDataSource",
        matchIfMissing = true
    )
    static class Hikari {
        Hikari() {
        }

        @Bean
        @ConfigurationProperties(
            prefix = "spring.datasource.hikari"
        )
        HikariDataSource dataSource(DataSourceProperties properties) {
            HikariDataSource dataSource = (HikariDataSource)DataSourceConfiguration.createDataSource(properties, HikariDataSource.class);
            if (StringUtils.hasText(properties.getName())) {
                dataSource.setPoolName(properties.getName());
            }

            return dataSource;
        }
    }
```

说明容器中没有`DataSource.class`才会导入我们的Hikari数据源

```java

@Configuration
public class MyDataSourceCofig {

 @ConfigurationProperties("spring.datasource")
 @Bean
 public DataSource dataSource(){
  DruidDataSource druidDataSource = new DruidDataSource();

//  druidDataSource.setUrl();
//  druidDataSource.setUsername();
//  druidDataSource.setPassword();
//  druidDataSource.setDriver();
  return druidDataSource;
 }
}
```

用`@ConfigurationProperties("spring.datasource")`注解去绑定我们的之前在yaml下面的数据类型

进行测试

```java
@Slf4j
@SpringBootTest
class BootWebAdminApplicationTests {
    @Autowired
    JdbcTemplate jdbcTemplate;
    @Autowired
    DataSource dataSource;
    @Test
    void contextLoads() {
        Long aLong = jdbcTemplate.queryForObject("select count(*) from tbl_emp", Long.class);
        log.info("记录总数为{}",aLong);
        log.info("容器中的数据源是{}",dataSource.getClass());
    }

}
```

结果如下

![image-20211010002541670](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010002541670.png)

我们还可以开启自定义下的对应功能来学习在Springboot放DataSource、servlet、Filter

1. **打开Druid的监控统计功能**

   ![image-20211010112046278](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010112046278.png)

   即对应在dataSource里面配置一个属性filters值为stat

```java
 @ConfigurationProperties("spring.datasource")
 @Bean
 public DataSource dataSource() throws SQLException {
  DruidDataSource druidDataSource = new DruidDataSource();
  druidDataSource.setFilters("stat");
  return druidDataSource;
 }
```



2. **打开Druid内置监控**

![image-20211010003026120](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010003026120.png)



我们现在只要在配置下注册进去即可，我们要 `ServletRegistrationBean`来进行 `Servlet`的注册，其中有构造方法

```java
      public ServletRegistrationBean(T servlet, String... urlMappings) {
          this(servlet, true, urlMappings);
      }
```

即

```java
 @Bean
 public ServletRegistrationBean statViewServlet(){

  StatViewServlet statViewServlet = new StatViewServlet();
  ServletRegistrationBean<StatViewServlet> bean = new ServletRegistrationBean<>(statViewServlet, "/druid/*");
  return bean;
 }
```

访问/druid

![image-20211010004212164](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010004212164.png)



![image-20211010112414012](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010112414012.png)

可以在druid官方文档里面查看对应的具体值的含义

3. **Web关联监控配置**

   ![image-20211010113148061](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010113148061.png)

```java
 @Bean
 public FilterRegistrationBean webStatFilter(){
  WebStatFilter webStatFilter = new WebStatFilter();
  FilterRegistrationBean<WebStatFilter> bean = new FilterRegistrationBean<>(webStatFilter);
  bean.setUrlPatterns(Arrays.asList("/*")); //对应的路径
  bean.addInitParameter("exclusions","*.js,*.gif,*.jpg,*.png,*.css,*.ico,/druid/*"); //初始化参数
  return bean;
 }
```

![image-20211010114146526](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010114146526.png)

![image-20211010114200395](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010114200395.png)

4. **怎么防御SQL注入攻击**

![image-20211010114347108](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010114347108.png)

```java
 @ConfigurationProperties("spring.datasource")
 @Bean
 public DataSource dataSource() throws SQLException {
  DruidDataSource druidDataSource = new DruidDataSource();
  druidDataSource.setFilters("stat,wall"); //多个值逗号分隔
  return druidDataSource;
 }
```

![image-20211010114558730](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010114558730.png)

5. **配置只有管理员才能访问**

![image-20211010115015036](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010115015036.png)

```java
 @Bean
 public ServletRegistrationBean statViewServlet(){

  StatViewServlet statViewServlet = new StatViewServlet();
  ServletRegistrationBean<StatViewServlet> bean = new ServletRegistrationBean<>(statViewServlet, "/druid/*");
  bean.addInitParameter("loginUsername","admin");
  bean.addInitParameter("loginPassword","123456");
  return bean;
 }
```

![image-20211010115150327](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010115150327.png)

我们也可以在`yaml`下直接写，因为我们绑定了配置文件

### 3.2.3、使用官方Starter方式

#### 1、引入druid-starter

```xml
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid-spring-boot-starter</artifactId>
            <version>1.1.17</version>
        </dependency>
```



#### 2、分析自动配置

进入自动配置类里面，我们可以得知

```java
@Configuration
@ConditionalOnClass({DruidDataSource.class})
@AutoConfigureBefore({DataSourceAutoConfiguration.class})
@EnableConfigurationProperties({DruidStatProperties.class, DataSourceProperties.class})
@Import({DruidSpringAopConfiguration.class, DruidStatViewServletConfiguration.class, DruidWebStatFilterConfiguration.class, DruidFilterConfiguration.class})
public class DruidDataSourceAutoConfigure {
    private static final Logger LOGGER = LoggerFactory.getLogger(DruidDataSourceAutoConfigure.class);

    public DruidDataSourceAutoConfigure() {
    }

    @Bean(
        initMethod = "init"
    )
    @ConditionalOnMissingBean
    public DataSource dataSource() {
        LOGGER.info("Init DruidDataSource");
        return new DruidDataSourceWrapper();
    }
}
```



- 扩展配置项在配置文件的前缀是`spring.datasource.druid`

其中导入四个class

- DruidSpringAopConfiguration.class

> 是用来监控SpringBean（组件）的，对应的配置项：spring.datasource.druid.aop-patterns

- DruidStatViewServletConfiguration.class

> 来开启监控页，对应的配置：spring.datasource.druid.stat-view-servlet，它是默认开启

-  DruidWebStatFilterConfiguration.class

> 用来配置web监控，对应的配置spring.datasource.druid.web-stat-filter，它是默认开启

- DruidFilterConfiguration.class

> 所有Druid自己filter的配置，把这些组件加载进去

```java
    private static final String FILTER_STAT_PREFIX = "spring.datasource.druid.filter.stat";
    private static final String FILTER_CONFIG_PREFIX = "spring.datasource.druid.filter.config";
    private static final String FILTER_ENCODING_PREFIX = "spring.datasource.druid.filter.encoding";
    private static final String FILTER_SLF4J_PREFIX = "spring.datasource.druid.filter.slf4j";
    private static final String FILTER_LOG4J_PREFIX = "spring.datasource.druid.filter.log4j";
    private static final String FILTER_LOG4J2_PREFIX = "spring.datasource.druid.filter.log4j2";
    private static final String FILTER_COMMONS_LOG_PREFIX = "spring.datasource.druid.filter.commons-log";
    private static final String FILTER_WALL_PREFIX = "spring.datasource.druid.filter.wall";
```



#### 3、配置示例

我们可以查看配置的前缀以后点击对应的`enabled`可以看到对应的属性

```yaml
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/db_account
    username: root
    password: 123456
    driver-class-name: com.mysql.jdbc.Driver

    druid:
      aop-patterns: com.atguigu.admin.*  #这个包下面的所有东西都监控，监控SpringBean，即所有组件
      filters: stat,wall     # 底层开启功能，stat（sql监控），wall（防火墙）

      stat-view-servlet:   # 配置监控页功能
        enabled: true
        login-username: admin
        login-password: 123456
        resetEnable: false #重置

      web-stat-filter:  # 监控web
        enabled: true
        urlPattern: /*
        exclusions: '*.js,*.gif,*.jpg,*.png,*.css,*.ico,/druid/*'


      filter:
        stat:    # 对上面filters里面的stat的详细配置
          slow-sql-millis: 1000 #慢查询
          logSlowSql: true
          enabled: true
        wall:
          enabled: true
          config:
            drop-table-allow: false
```

SpringBoot配置示例

https://github.com/alibaba/druid/tree/master/druid-spring-boot-starter



配置项列表[https://github.com/alibaba/druid/wiki/DruidDataSource%E9%85%8D%E7%BD%AE%E5%B1%9E%E6%80%A7%E5%88%97%E8%A1%A8](https://github.com/alibaba/druid/wiki/DruidDataSource配置属性列表)

气死了家人们！

## 3.3、整合MyBatis操作

https://github.com/mybatis

starter

SpringBoot官方的Starter：spring-boot-starter-*

第三方的： *-spring-boot-starter

```xml
        <dependency>
            <groupId>org.mybatis.spring.boot</groupId>
            <artifactId>mybatis-spring-boot-starter</artifactId>
            <version>2.2.0</version>
        </dependency>
```

![image-20211010162629065](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010162629065.png)

可以把jdbc给开除了！

### 1、配置模式

以前我们的使用Mybatis的必要

- 全局配置文件
- SqlSessionFactory

> `MybatisAutoConfiguration`自动配置好了

- SqlSession

> `MybatisAutoConfiguration`自动配置了 `SqlSessionTemplate`，在里面组合了`SqlSession`

其中

```java
@Configuration
@Import({MybatisAutoConfiguration.AutoConfiguredMapperScannerRegistrar.class}) //重点
@ConditionalOnMissingBean({MapperFactoryBean.class, MapperScannerConfigurer.class})
public static class MapperScannerRegistrarNotFoundConfiguration implements InitializingBean {}
```

其中`@Import(AutoConfiguredMapperScannerRegistrar.class)`定义了我们的写的操作MyBatis的接口标明了 **`@Mapper` **就会被自动扫描进来

Springboot一启动起来，然后会找`EnableAutoConfiguration`下我们要开启的所有配置

```factories
# Auto Configure
org.springframework.boot.autoconfigure.EnableAutoConfiguration=\
org.mybatis.spring.boot.autoconfigure.MybatisLanguageDriverAutoConfiguration,\
org.mybatis.spring.boot.autoconfigure.MybatisAutoConfiguration
```

这里我们主要分析我们的`MybatisAutoConfiguration`

```java
@Configuration
@ConditionalOnClass({SqlSessionFactory.class, SqlSessionFactoryBean.class})
@ConditionalOnSingleCandidate(DataSource.class)
@EnableConfigurationProperties({MybatisProperties.class})
@AutoConfigureAfter({DataSourceAutoConfiguration.class, MybatisLanguageDriverAutoConfiguration.class})
public class MybatisAutoConfiguration implements InitializingBean {}
```

对应的配置文件

```java
@ConfigurationProperties(
    prefix = "mybatis"
)
public class MybatisProperties {}
```

可以知道我们的配置文件前缀为**`mybatis`**

```java
@EnableConfigurationProperties(MybatisProperties.class) ： MyBatis配置项绑定类。
@AutoConfigureAfter({ DataSourceAutoConfiguration.class, MybatisLanguageDriverAutoConfiguration.class })
public class MybatisAutoConfiguration{}

@ConfigurationProperties(prefix = "mybatis")
public class MybatisProperties
```

可以修改配置文件中 `mybatis` 开始的所有；

我们要配置的东西：一个是配置文件位置和映射xml的位置

```yaml
##配置mybatis的两个规则
##一个是配置文件位置和映射xml的位置
mybatis:
  config-location: classpath:mybatis/mybatis-config.xml
  mapper-locations: classpath:mybatis/mapper/*.xml
```

我们推荐

对应resource

```txt
resource
	-mybatis
		-mapper
			-xxxMapper.xml
			-.....
     mybatis-config.xml   
```

对应的java

```txt
com
	-ceit
		-admin
			-bean
				xxx(实体类)
            -Mapper
            	xxxMapper(对应类的接口)
```

对应的mybatis-config.xml，啥也不用写，我们的数据源因为在3.1.3已经配置好了，然后对应的mapper的映射在spring被整合以后在mvc里面也在上面配置好了。

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
  PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
   
</configuration>
```

> 我推荐所有用户在对应mybatis里面进行驼峰命名的开启，或者进行对应的resultMap配置

我们在`MybatisProperties.class`里面的

```java
    private Configuration configuration;
```

的对应里面

```java
    protected Environment environment;
    protected boolean safeRowBoundsEnabled;
    protected boolean safeResultHandlerEnabled;
    protected boolean mapUnderscoreToCamelCase;
    protected boolean aggressiveLazyLoading;
    protected boolean multipleResultSetsEnabled;
    protected boolean useGeneratedKeys;
    protected boolean useColumnLabel;
    protected boolean cacheEnabled;
    protected boolean callSettersOnNulls;
    protected boolean useActualParamName;
    protected boolean returnInstanceForEmptyRow;
    protected boolean shrinkWhitespacesInSql;
```

我们可以在yaml里面这么写

```yaml
mybatis:
  config-location: classpath:mybatis/mybatis-config.xml
  mapper-locations: classpath:mybatis/mapper/*.xml
  configuration:
    map-underscore-to-camel-case: true
```

最后通过这个`configuration`我们决定我们把配置文件省略掉，所有配置都在`configuration`里面写就得了

```yaml
mybatis:
  mapper-locations: classpath:mybatis/mapper/*.xml
  configuration:
    map-underscore-to-camel-case: true
```

**这样`mybatis`下的`mybatis-config.xml`也可以删除了哦**



**总结：**

1. 导入mybatis官方starter
2. 编写mapper接口。标准@Mapper注解
3. 编写sql映射文件并绑定mapper接口
4. 在application.yaml中指定Mapper配置文件的位置

### 2、注解模式

```java
@Mapper
public interface CityMapper {

    @Select("select * from city where id=#{id}")
    public City getById(Long id);

}
```

### 3、混合模式

```java
@Mapper
public interface CityMapper {

    @Select("select * from city where id=#{id}")
    public City getById(Long id);

    public void insert(City city);

}
```

**我们过一遍流程**：

1. bean

```java
@Data
public class department {
    private Integer deptId;
    private String deptName;
}
```

2. mapper

```java
@Mapper
public interface departmentMapper {
    public department getdept(int id);
}
```

3. mapper.xml

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.ceit.admin.Mapper.departmentMapper">
<resultMap id="dept" type="com.ceit.admin.bean.department">
    <result column="dept_id" property="deptId"></result>
    <result column="dept_name" property="deptName"></result>
</resultMap>

    <select id="getdept" resultMap="dept">
        select * from tnl_dept where dept_id = #{id};
    </select>
</mapper>
```

4. service

```java
@Service
public class departmentService {
    @Autowired
    departmentMapper departmentMapper;

    public department getdeptById(int id){
      return   departmentMapper.getdept(id);
    }
}
```

5. Controller

```java
    @ResponseBody
    @GetMapping("/dept")
    public department getDepartmentById(@RequestParam("id") int id){
        department dept = departmentService.getdeptById(id);
        return dept;
    }
```

6.  测试

![image-20211010200130235](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211010200130235.png)最佳实战：

- 简单方法直接注解方式

- 复杂方法编写mapper.xml进行绑定映射
- 我们喜欢在总启动文件里面写上注释`@MapperScan("com.ceit.admin.mapper") `简化，其他的接口就可以不用标注@`Mapper`注解



## 3.4、整合 MyBatis-Plus 完成CRUD

### 1、什么是MyBatis-Plus

[MyBatis-Plus](https://github.com/baomidou/mybatis-plus)（简称 MP）是一个 [MyBatis](http://www.mybatis.org/mybatis-3/) 的增强工具，在 MyBatis 的基础上只做增强不做改变，为简化开发、提高效率而生。

[mybatis plus 官网](https://baomidou.com/)

建议安装 **MybatisX** 插件 



### 2、整合MyBatis-Plus

```xml
        <dependency>
            <groupId>com.baomidou</groupId>
            <artifactId>mybatis-plus-boot-starter</artifactId>
            <version>3.4.1</version>
        </dependency>
```

我们发现我们的mybatis-plus自动帮我们很多包，我们可以把对应的mybatis的包给导出了

我们看这个包，Springboot一启动起来，然后会找`EnableAutoConfiguration`下我们要开启的所有配置

- `MybatisPlusAutoConfiguration` 配置类，`MybatisPlusProperties` 配置项绑定。对应的配置前缀是`mybatis-plus`

```factories
# Auto Configure
org.springframework.boot.env.EnvironmentPostProcessor=\
  com.baomidou.mybatisplus.autoconfigure.SafetyEncryptProcessor
org.springframework.boot.autoconfigure.EnableAutoConfiguration=\
  com.baomidou.mybatisplus.autoconfigure.IdentifierGeneratorAutoConfiguration,\
  com.baomidou.mybatisplus.autoconfigure.MybatisPlusLanguageDriverAutoConfiguration,\
  com.baomidou.mybatisplus.autoconfigure.MybatisPlusAutoConfiguration
```

- `SqlSessionFactory` 自动配置好。底层是容器中默认的数据源

```java
@Bean
    @ConditionalOnMissingBean
    public SqlSessionFactory sqlSessionFactory(DataSource dataSource) throws Exception {}
```

- `mapperLocations` 自动配置好的。有默认值。

```java
  private String[] mapperLocations = new String[]{"classpath*:/mapper/**/*.xml"};
```

即任意包下mapper文件夹下的任意路径下的所有xml文件，即对应的

```txt
resource
	-mapper
		xxx.xml
		.....
```

**我们建议这种操作**

- 容器中也自动配置好了SqlSessionTemplate

```java
    @Bean
    @ConditionalOnMissingBean
    public SqlSessionTemplate sqlSessionTemplate(SqlSessionFactory sqlSessionFactory) {
        ExecutorType executorType = this.properties.getExecutorType();
        return executorType != null ? new SqlSessionTemplate(sqlSessionFactory, executorType) : new SqlSessionTemplate(sqlSessionFactory);
    }
```

- `@Mapper` 标注的接口也会被自动扫描；启动类`@MapperScan("com.ceit.admin.mapper")` 批量扫描就行

```java
    @Configuration(
        proxyBeanMethods = false
    )
    @Import({MybatisPlusAutoConfiguration.AutoConfiguredMapperScannerRegistrar.class}) //注册Mapper注册信息
    @ConditionalOnMissingBean({MapperFactoryBean.class, MapperScannerConfigurer.class})
    public static class MapperScannerRegistrarNotFoundConfiguration implements InitializingBean {
        public MapperScannerRegistrarNotFoundConfiguration() {
        }
```

- 记得和3.1一样配置数据源哦！！



**优点：**

-  只需要我们的Mapper继承 **BaseMapper** 就可以拥有crud能力

```java
public interface BaseMapper<T> extends Mapper<T> {
    int insert(T entity);

    int deleteById(Serializable id);

    int deleteById(T entity);

    int deleteByMap(@Param("cm") Map<String, Object> columnMap);

    int delete(@Param("ew") Wrapper<T> queryWrapper);

    int deleteBatchIds(@Param("coll") Collection<? extends Serializable> idList);

    int updateById(@Param("et") T entity);

    int update(@Param("et") T entity, @Param("ew") Wrapper<T> updateWrapper);

    T selectById(Serializable id);

    List<T> selectBatchIds(@Param("coll") Collection<? extends Serializable> idList);

    List<T> selectByMap(@Param("cm") Map<String, Object> columnMap);

    default T selectOne(@Param("ew") Wrapper<T> queryWrapper) {
        List<T> ts = this.selectList(queryWrapper);
        if (CollectionUtils.isNotEmpty(ts)) {
            if (ts.size() != 1) {
                throw ExceptionUtils.mpe("One record is expected, but the query result is multiple records", new Object[0]);
            } else {
                return ts.get(0);
            }
        } else {
            return null;
        }
    }

    Long selectCount(@Param("ew") Wrapper<T> queryWrapper);

    List<T> selectList(@Param("ew") Wrapper<T> queryWrapper);

    List<Map<String, Object>> selectMaps(@Param("ew") Wrapper<T> queryWrapper);

    List<Object> selectObjs(@Param("ew") Wrapper<T> queryWrapper);

    <P extends IPage<T>> P selectPage(P page, @Param("ew") Wrapper<T> queryWrapper);

    <P extends IPage<Map<String, Object>>> P selectMapsPage(P page, @Param("ew") Wrapper<T> queryWrapper);
}
```

我们居然就可以拥有增删改查方法，真牛啊真牛啊！

但是，我们要是数据库里面的属性和bean里面的属性不一样就会报错，我们推荐使用`@TableField(exist = false)`来告诉Springboot没有它！

```java
@TableField(exist = false)
private String userName;
@TableField(exist = false)
private String password;
```

哪假如我们的bean里面的实体类和数据库里面的表名不一样呢？假如数据库里面是user_tbl，bean里实体类是user，怎么办呢？我们就需要在我们的实体类里面添加`@TableName("user_tbl")`



注意我们的规范：因为我们的IOC切面的原因，我们一般

- 在Controller里面自动注入是我们的Service接口
- 在Service里面应该是这样的结构

```txt
Service
	-Impl
		xxxxImpl
		....
    xxxService(接口)
    .....
```

> 注意我们的@Service要写在我们的实现类哦

这个时候我们又发现

我们自动注入我们的Service时候又要调用我们的userMapper来执行，这样一看真麻烦啊,于是我们在UserService接口`extends IService<> `

```java
public interface UserService extends IService<User> {
}
```

然后又对应了的`@Service`

```java
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper,User> implements UserService {
}
```

我们复杂的增删改查就得了

### 3、CRUD功能

下面我们将使用我们的mybatis-plus来进行完成数据表格和增删改查的功能

![image-20211011141855374](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211011141855374.png)

所以，当我们想展示数据的同时，我们肯定页需要我们的分页功能，我们直接使用我们的分页构造函数来构造我们的页面

Mybatis的分页功能需要我们自己编写一个`MybatisPlusConifg`配置文件

```java
@Configuration
public class MybatisPlusConfig {
    // 最新版
    @Bean
    public MybatisPlusInterceptor mybatisPlusInterceptor() {
        MybatisPlusInterceptor interceptor = new MybatisPlusInterceptor();
        interceptor.addInnerInterceptor(new PaginationInnerInterceptor(DbType.H2));
        return interceptor;
    }
}
```

现在我们来分析page的强大功能

```java
    default <E extends IPage<T>> E page(E page, Wrapper<T> queryWrapper) {
        return getBaseMapper().selectPage(page, queryWrapper);
    }
```

其中我们这个方法中有两个参数

![image-20211011151729910](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211011151729910.png)

我们的前一个对象page是继承 IPage<T>的，我们可以使用ctrl+H来看看有没有实体类实现了它

![image-20211011152422236](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211011152422236.png)

我们发现Page实现了它，我们进入它的实现类，这里我们简单展示，并不是该class的全部

> 这里是Page类，上面是page方法

```java
public class Page<T> implements IPage<T> {

    private static final long serialVersionUID = 8545996863226528798L;

    /**
     * 查询数据列表
     */
    protected List<T> records = Collections.emptyList();

    /**
     * 总数
     */
    protected long total = 0;
    /**
     * 每页显示条数，默认 10
     */
    protected long size = 10;

    /**
     * 当前页
     */
    protected long current = 1;

    /**
     * 排序字段信息
     */
    @Setter
    protected List<OrderItem> orders = new ArrayList<>();

    /**
     * 自动优化 COUNT SQL
     */
    protected boolean optimizeCountSql = true;
    /**
     * 是否进行 count 查询
     */
    protected boolean searchCount = true;
    /**
     * {@link #optimizeJoinOfCountSql()}
     */
    @Setter
    protected boolean optimizeJoinOfCountSql = true;
    /**
     * countId
     */
    @Setter
    protected String countId;
    /**
     * countId
     */
    @Setter
    protected Long maxLimit;
    
        public Page(long current, long size) {
        this(current, size, 0);
    }

    public Page(long current, long size, long total) {
        this(current, size, total, true);
    }

    public Page(long current, long size, boolean searchCount) {
        this(current, size, 0, searchCount);
    }

    public Page(long current, long size, long total, boolean searchCount) {
        if (current > 1) {
            this.current = current;
        }
        this.size = size;
        this.total = total;
        this.searchCount = searchCount;
    }
    
        @Override
    public long getPages() {   //这个方法是继承了IPage类的getpage方法，目的是返回当前分页的总页数，是我们经常使用的方法
        // 解决 github issues/3208
        return IPage.super.getPages();
    }

```

我们要先构造一个Page对象，即需要我们的当前页和每一页展示的多少条数据

- 当前页由前端返回
- 展示多少条数据可以在Controller里面写死，但我们不推荐这种做法，而是在前端控制给用户来选择，我们这里先默认写死为

```java
        //分页查询数据
        Page<User> userPage = new Page<>(pn, 2);
        //分页查询结果
        Page<User> page = userService.page(userPage, null); //null表示无条件查询，后面我们将添加我们的条件查询
```

此时我们将我们的Controller完善

```java
    @GetMapping("/dynamic_table") //设置请求域里面前端发送请求时候带pn=XXX，如果没有则默认为1
    public String dynamic_table(@RequestParam(value = "pn",defaultValue = "1")Integer pn, Model model){
        //分页查询数据
        Page<User> userPage = new Page<>(pn, 2);
        //分页查询结果
        Page<User> page = userService.page(userPage, null);
        
        model.addAttribute("page",page);
        return "table/dynamic_table";
    }
```

前端则是这样写

```html
<table class="display table table-bordered table-striped" id="dynamic-table">
    <thead>
        <tr>
            <th>#</th>
            <th>id</th>
            <th>name</th>
            <th>age</th>
            <th>email</th>
            <th>操作</th>
        </tr>
    </thead>
    <tbody role="alert" aria-live="polite" aria-relevant="all">
        <tr class="gradeX odd" th:each="user,stat:${page.records}">
            <td th:text="${stat.count}"></td>
            <td th:text="${user.id}"></td>
            <td th:text="${user.name}"></td>
            <td th:text="${user.age}"></td>
            <td class="center hidden-phone">[[${user.email}]]</td>
                                        <td>
                                            <a th:href="@{/user/delete/{id}(id=${user.id},pn=${page.current})}" class="btn btn-danger btn-sm" type="button">删除</a>
                                        </td>
        </tr>
    </tbody>
    <tfoot>
    </tfoot>
</table>
<div class="row-fluid">
    <div class="span6">
        <div class="dataTables_info" id="dynamic-table_info">当前第[[${page.current}]]页 总计[[${page.pages}]] 页 共
            [[${page.total}]] 记录
        </div>
    </div>
    <div class="span6">
        <div class="dataTables_paginate paging_bootstrap pagination">
            <ul>
                <li class="prev disabled"><a href="#">← 前一页</a></li>
                <li th:class="${num==page.current?'active':''}" th:each="num:${#numbers.sequence(1,page.pages)}">
                    <a th:href="@{/dynamic_table(pn=${num})}">[[${num}]]</a></li>
                <li class="next disabled"><a href="#">下一页 → </a></li>
            </ul>
        </div>
    </div>
</div>
```

接下来我们将加入我们的增删功能，记得Ctrl + Alt + L

```java
    @GetMapping("/user/delete/{id}")   //当我们点击我们的删除按钮th:href="@{/user/delete/{id}(id=${user.id},pn=${page.current})}"，我们的请求传入两个参数分别是id域和pn请求
    public String deleteUser(@PathVariable("id") Long id,  
                             @RequestParam(value = "pn",defaultValue = "1") Integer pn, // 默认是1
                             RedirectAttributes ra
    ){
        userService.removeById(id);
        ra.addAttribute("pn",pn);

        return "redirect:/dynamic_table";
    }    

	@GetMapping("/dynamic_table")
    public String dynamic_table(@RequestParam(value = "pn",defaultValue = "1")Integer pn, Model model){//?pn=...
        //从数据库中查出user表的用户并展示
        List<User> list = userService.list();

        //分页查询数据
        Page<User> userPage = new Page<>(pn, 2);
        //分页查询结果
        Page<User> page = userService.page(userPage, null);

//        model.addAttribute("userList",list);
        model.addAttribute("page",page);
        return "table/dynamic_table";
    }
```













```java
    @GetMapping("/user/delete/{id}")
    public String deleteUser(@PathVariable("id") Long id,
                             @RequestParam(value = "pn",defaultValue = "1")Integer pn,
                             RedirectAttributes ra){

        userService.removeById(id);

        ra.addAttribute("pn",pn);
        return "redirect:/dynamic_table";
    }


    @GetMapping("/dynamic_table")
    public String dynamic_table(@RequestParam(value="pn",defaultValue = "1") Integer pn,Model model){
        //表格内容的遍历
//        response.sendError
//     List<User> users = Arrays.asList(new User("zhangsan", "123456"),
//                new User("lisi", "123444"),
//                new User("haha", "aaaaa"),
//                new User("hehe ", "aaddd"));
//        model.addAttribute("users",users);
//
//        if(users.size()>3){
//            throw new UserTooManyException();
//        }
        //从数据库中查出user表中的用户进行展示

        //构造分页参数
        Page<User> page = new Page<>(pn, 2);
        //调用page进行分页
        Page<User> userPage = userService.page(page, null);


//        userPage.getRecords()
//        userPage.getCurrent()
//        userPage.getPages()


        model.addAttribute("users",userPage);

        return "table/dynamic_table";
    }
```



```java
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper,User> implements UserService {


}

public interface UserService extends IService<User> {

}
```

# 2、NoSQL

Redis 是一个开源（BSD许可）的，内存中的数据结构存储系统，它可以用作数据库、**缓存**和消息中间件。 它支持多种类型的数据结构，如 [字符串（strings）](http://www.redis.cn/topics/data-types-intro.html#strings)， [散列（hashes）](http://www.redis.cn/topics/data-types-intro.html#hashes)， [列表（lists）](http://www.redis.cn/topics/data-types-intro.html#lists)， [集合（sets）](http://www.redis.cn/topics/data-types-intro.html#sets)， [有序集合（sorted sets）](http://www.redis.cn/topics/data-types-intro.html#sorted-sets) 与范围查询， [bitmaps](http://www.redis.cn/topics/data-types-intro.html#bitmaps)， [hyperloglogs](http://www.redis.cn/topics/data-types-intro.html#hyperloglogs) 和 [地理空间（geospatial）](http://www.redis.cn/commands/geoadd.html) 索引半径查询。 Redis 内置了 [复制（replication）](http://www.redis.cn/topics/replication.html)，[LUA脚本（Lua scripting）](http://www.redis.cn/commands/eval.html)， [LRU驱动事件（LRU eviction）](http://www.redis.cn/topics/lru-cache.html)，[事务（transactions）](http://www.redis.cn/topics/transactions.html) 和不同级别的 [磁盘持久化（persistence）](http://www.redis.cn/topics/persistence.html)， 并通过 [Redis哨兵（Sentinel）](http://www.redis.cn/topics/sentinel.html)和自动 [分区（Cluster）](http://www.redis.cn/topics/cluster-tutorial.html)提供高可用性（high availability）。

## 1、Redis自动配置

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-redis</artifactId>
        </dependency>
```

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1606745732785-17d1227a-75b9-4f00-a3f1-7fc4137b5113.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_17%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)



自动配置：

- RedisAutoConfiguration 自动配置类。RedisProperties 属性类 --> **spring.redis.xxx是对redis的配置**
- 连接工厂是准备好的。**Lettuce**ConnectionConfiguration、**Jedis**ConnectionConfiguration

- **自动注入了RedisTemplate**<**Object**, **Object**> ： xxxTemplate；
- **自动注入了StringRedisTemplate；k：v都是String**

- **key：value**
- **底层只要我们使用** **StringRedisTemplate、****RedisTemplate就可以操作redis**





**redis环境搭建**

**1、阿里云按量付费redis。经典网络**

**2、申请redis的公网连接地址**

**3、修改白名单  允许0.0.0.0/0 访问**







## 2、RedisTemplate与Lettuce



```java
    @Test
    void testRedis(){
        ValueOperations<String, String> operations = redisTemplate.opsForValue();

        operations.set("hello","world");

        String hello = operations.get("hello");
        System.out.println(hello);
    }
```









## 3、切换至jedis

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-redis</artifactId>
        </dependency>

<!--        导入jedis-->
        <dependency>
            <groupId>redis.clients</groupId>
            <artifactId>jedis</artifactId>
        </dependency>
spring:
  redis:
      host: r-bp1nc7reqesxisgxpipd.redis.rds.aliyuncs.com
      port: 6379
      password: lfy:Lfy123456
      client-type: jedis
      jedis:
        pool:
          max-active: 10
```
