@[TOC](Web框架整合)

# 1.前提
 - 掌握JavaWeb
 - 掌握Mybatis
 - 掌握Spring
 - 掌握SpringMvc

 ![在这里插入图片描述](https://img-blog.csdnimg.cn/1407b9210bf94428911aef91272f9774.png)

## 1.2 创建数据库

```sql
CREATE DATABASE `ssmbuild`;

USE `ssmbuild`;

CREATE TABLE `books`(
`bookID` INT(10) NOT NULL AUTO_INCREMENT COMMENT ‘书id’,
`bookName` VARCHAR(100) NOT NULL COMMENT ‘书名’,
`bookCounts` INT(11) NOT NULL COMMENT ‘数量’,
`detail` VARCHAR(200) NOT NULL COMMENT ‘描述’,
KEY `bookID`(`bookID`)
)ENGINE=INNODB DEFAULT CHARSET=utf8;

INSERT INTO `books`(`bookID`,`bookName`,`bookCounts`,`detail`) VALUES
(1,'Java',1,'从入门到放弃'),
(2,'MySQL',10,'从删库到跑路'),
(3,'Linux',5,'从进门到进牢');
```
## 1.3 创建配置文件


```xml
<!--依赖问题junit，数据库驱动，连接池，Servlet，jsp，mybatis，mybatis-spring-->
    <dependencies>
<!--junit-->
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.13.2</version>
            <scope>test</scope>
        </dependency>
<!--数据库驱动-->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.25</version>
        </dependency>
<!--数据库连接池-->
        <dependency>
            <groupId>com.mchange</groupId>
            <artifactId>c3p0</artifactId>
            <version>0.9.5.5</version>
        </dependency>
<!--servlet-->
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>servlet-api</artifactId>
            <version>2.5</version>
        </dependency>
<!--jsp-->
        <dependency>
            <groupId>javax.servlet.jsp</groupId>
            <artifactId>jsp-api</artifactId>
            <version>2.2</version>
        </dependency>
<!--jsp相关-->
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>jstl</artifactId>
            <version>1.2</version>
        </dependency>
<!--mybatis-->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.7</version>
        </dependency>
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis-spring</artifactId>
            <version>2.0.6</version>
        </dependency>
<!--spring-->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-webmvc</artifactId>
            <version>5.3.9</version>
        </dependency>
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-jdbc</artifactId>
            <version>5.3.9</version>
        </dependency>
<!--aspest-->
        <dependency>
            <groupId>org.aspectj</groupId>
            <artifactId>aspectjweaver</artifactId>
            <version>1.9.4</version>
        </dependency>
<!--lombok-->
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <version>1.18.12</version>
        </dependency>
    </dependencies>
<!--静态资源导出问题-->
    <build>
        <resources>
            <resource>
                <directory>src/main/java</directory>
                <includes>
                    <include>**/*.properties</include>
                    <include>**/*.xml</include>
                </includes>
                <filtering>false</filtering>
            </resource>
            <resource>
                <directory>src/main/resources</directory>
                <includes>
                    <include>**/*.properties</include>
                    <include>**/*.xml</include>
                </includes>
                <filtering>false</filtering>
            </resource>
        </resources>
    </build>
```
## 1.4 建立对应包类
在`java`文件夹
```text
com.ceit.pojo
com.ceit.dao
com.ceit.service
com.ceit.controller
com.ceit.utils
com.ceit.filter
```
在`resources`文件夹

```text
mybatis-config.xml
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration></configuration>
```




```text
applicationContext.xml
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd">

</beans>
```
## 1.5 配置数据库连接需求
 编写`properties`文件

```text
# 第一个是数据库驱动
jdbc.drive =com.mysql.cj.jdbc.Driver

# 对应的url端口，如果使用高版本的是我们的要增加时区的配置&serverTimezone=UTC
# 格式为 jdbc:mysql://localhost:3306/*(*代表数据库名)?useSSL=false&useUnicode=true&characterEncoding=utf-8&&serverTimezone=UTC
jdbc.url = jdbc:mysql://localhost:3306/ssmbuild?useSSL=false&useUnicode=true&characterEncoding=utf-8

#对应数据库登入用户和密码
jdbc.username=root
jdbc.password=123456
```
## 1.6 编写核心类
我们的实体类要和数据库一一对应
```java
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Books {
    private int bookID;
    private String bookName;
    private  int bookCounts;
    private String detail;
}

```
# 2.配置mybatis层 
## 2.1 配置mybatis核心配置文件

```xml
    <typeAliases>
        <package name="com.ceit.pojo"/>
    </typeAliases>
```


## 2.3 Dao层
编写`BooksMapper`接口
这里的功能是对于需求分析而言，我们这里只写简单的增删改查四个语句
```java
public interface BooksMapper {
    //增加一本书
    int addBook(Books books);
    //删除一本书
    int deleteBook(int id);
    //修改一本书
    int updateBook(Books books);
    //查询一本书
    Books queryBookById(int id);
    //查询全部书
    List<Books> queryAllBook();
}

```
编写对应的mybatis的`BookMapper.xml`来连接接口
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.ceit.dao.BooksMapper">
</mapper>
```
一个xml有一个`<mapper namespace="">`对应唯一一个dao接口

**没有数据库提醒怎么办？**
![在这里插入图片描述](https://img-blog.csdnimg.cn/b65a77208865406e8fa7e22a870307eb.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
![在这里插入图片描述](https://img-blog.csdnimg.cn/37f55083b5c94db8ba66edf9e21df1eb.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
设置以后大幅度提高我们写mysql的效率

1. 编写`BookMapper.xml`
```xml
    <insert id="addBook" parameterType="books">
        insert into ssmbuild.books(bookID, bookName, bookCounts, detail)
        VALUES (#{bookName},#{bookCounts},#{detail});
    </insert>
    <delete id="deleteBook">
        delete from ssmbuild.books where bookID = #{bookId}
    </delete>
    <update id="updateBook" parameterType="books">
        update ssmbuild.books
        set bookName=#{bookName},bookCounts=#{bookCounts},detail=#{detail}
        where bookID=#{bookId}
    </update>
    <select id="queryBookById" resultType="com.ceit.pojo.Books">
        select * from ssmbuild.books where bookID=#{bookId}
    </select>
    <select id="queryAllBook" resultType="com.ceit.pojo.Books">
        select * from ssmbuild.books
    </select>
```
注意，我们的参数类型不是基本类型的时候要写，同时我们对象传参要和数据库字段一样，在类型传参要标定对于的`@Param("bookId")`来标志两个的对应


2. 修改`BooksMapper`

```java
public interface BooksMapper {
    //增加一本书
    int addBook(Books books);
    //删除一本书
    int deleteBook(@Param("bookId") int id);
    //修改一本书
    int updateBook(Books books);
    //查询一本书
    Books queryBookById(@Param("bookId") int id);
    //查询全部书
    List<Books> queryAllBook();
}

```

3. 在`mybatis-config.xml`配置文件

```xml
    <mappers>
        <mapper class="com.ceit.dao.BooksMapper"/>
    </mappers>
```
## 2.4 Service层
1. 编写对应的`BookService`接口

```java
public interface BookService {
    //增加一本书
    int addBook(Books books);
    //删除一本书
    int deleteBook(int id);
    //修改一本书
    int updateBook(Books books);
    //查询一本书
    Books queryBookById( int id);
    //查询全部书
    List<Books> queryAllBook();
}
```
这是普普通通的方法不用`@Param("")`来标识

2.  编写`BookService` 实现类，其中设置dao层对象，然后给它配置对应的set方法实现，我们用户就可以在Service层来从而自己调用dao层方法，**即业务层调用Dao层**

```java
public class BookServiceImpl implements BookService{

    //service层调用dao层:组合Dao
    private BookMapper bookMapper;
    public void setBooksMapper(BookMapper bookMapper){
        this.bookMapper = bookMapper;
    }

    @Override
    public int addBook(Books books) {
        return bookMapper.addBook(books);
    }

    @Override
    public int deleteBook(int id) {
        return bookMapper.deleteBook(id);
    }

    @Override
    public int updateBook(Books books) {
        return bookMapper.updateBook(books);
    }

    @Override
    public Books queryBookById(int id) {
        return bookMapper.queryBookById(id);
    }

    @Override
    public List<Books> queryAllBook() {
        return bookMapper.queryAllBook();
    }
}
```
# 3. 配置Spring层
## 3.1 Dao层
`spring-dao.xml`
```xml
    <!--1.关联数据库配置文件
     <context:property-placeholder location=""/>是Spring是专门来关联数据库文件的
    -->
    <context:property-placeholder location="classpath:database.properties"/>

    <!--2.连接池
        dbcp:半自动化操作，不能自动连接
        c3p0:自动化操作，自动化加载配置文件并且可以自动设置到对象中
        druid:
        hikari:-->
    <bean id="dataSource" class="com.mchange.v2.c3p0.ComboPooledDataSource">
        <property name="driverClass" value="${jdbc.drive}"/>
        <property name="jdbcUrl" value="${jdbc.url}"/>
        <property name="user" value="${jdbc.username}"/>
        <property name="password" value="${jdbc.password}"/>
    </bean>
    <!--3.SqlSessionFactory-->
    <bean class="org.mybatis.spring.SqlSessionFactoryBean" id="sqlSessionFactory">
        <property name="dataSource" ref="dataSource"/>
        <!--绑定配置文件-->
        <property name="configLocation" value="classpath:mybatis-config.xml"/>
    </bean>

    <!--配置Dao扫描包，动态实现了Dao接口可以注入到Spring容器中-->
    <bean class="org.mybatis.spring.mapper.MapperScannerConfigurer">
    <!-- 此时会在扫描的时候动态的把sqlSessionFactory加载到sqlSessionFactoryBeanName，即注入sqlSessionFactory-->
        <property name="sqlSessionFactoryBeanName" value="sqlSessionFactory"/>
    <!--扫描的Dao包-->
        <property name="basePackage" value="com.kuang.dao"/>
    </bean>
    <!--之前要写的实现类以后可以不用写了-->
```
## 3.2 Service层
`spring-service.xml`
```xml
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xmlns:tx="http://www.springframework.org/schema/tx"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd
        http://www.springframework.org/schema/tx
        http://www.springframework.org/schema/tx/spring-tx.xsd">
    <!--1.扫描Service下的包-->
    <context:component-scan base-package="com.ceit.service"/>
    <!--2.将我们的所有业务类注入到Spring，可以通过配置或者注解实现-->
    <bean id="BookServiceImpl" class="com.ceit.service.BookServiceImpl">
        <property name="bookMapper" ref="bookMapper"/>
    </bean>
    <!--3.声明式事务配置-->
    <bean class="org.springframework.jdbc.datasource.DataSourceTransactionManager" id="transactionManager">
        <!--注入数据源-->
        <property name="dataSource" ref="dataSource" />
    </bean>
        <!--4.aop事务支持-->
    <tx:advice id="txAdvice" transaction-manager="transactionManager">
        <tx:attributes>
            <tx:method name="*" propagation="REQUIRED"/>
        </tx:attributes>
    </tx:advice>
    <aop:config>
        <aop:pointcut id="txPointCut" expression="execution(* com.ceit.dao.*.*(..))"/>
        <aop:advisor advice-ref="txAdvice" pointcut-ref="txPointCut"/>
    </aop:config>

```
# 4.配置SpringMvc层
## 4.1 web配置

```xml
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:spring-mvc.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
    <servlet-mapping>
        <servlet-name>springmvc</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
    <!--乱码过滤-->
    <filter>
        <filter-name>encodingFilter</filter-name>
        <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
        <init-param>
            <param-name>encoding</param-name>
            <param-value>utf-8</param-value>
        </init-param>
    </filter>
    <filter-mapping>
        <filter-name>encodingFilter</filter-name>
        <url-pattern>/*</url-pattern>
    </filter-mapping>
    <session-config>
        <session-timeout>15</session-timeout>
    </session-config>
```
## 4.2 springmvc核心配置
1. `spring-mvc.xml`
```xml
<!--1.注解驱动-->
    <mvc:annotation-driven/>
<!--2.静态资源过滤-->
    <mvc:default-servlet-handler/>
<!--3.扫描包:controller-->
    <context:component-scan base-package="com.ceit.controller"/>
<!--4.视图解析器-->
    <bean class="org.springframework.web.servlet.view.InternalResourceViewResolver">
        <property name="prefix" value="/WEB-INF/jsp"></property>
        <property name="suffix" value=".jsp"></property>
    </bean>
```
2. 在WEB-INF下面建立jsp文件夹


# 5. 配置前端
推荐使用bootstrap可视化布局