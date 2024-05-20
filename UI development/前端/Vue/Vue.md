# 什么是Vue

`Vue`是一套用于构建用户界面的`JavaScript`**渐进式框架**。

- 与其它大型框架不同的是，`Vue `被设计为可以自底向上逐层应用。
- `Vue` 的核心库只关注视图层，不仅易于上手，还便于与第三方库或既有项目整合。
- 另一方面，当与[现代化的工具链](https://cn.vuejs.org/v2/guide/single-file-components.html)以及各种[支持类库](https://github.com/vuejs/awesome-vue#libraries--plugins)结合使用时，`Vue` 也完全能够为复杂的单页应用提供驱动。
- 提供了一套声明式的、组件化的编程模型，帮助你高效地开发用户界面。

我们可以在官网上下载对应的`Vue.js`

并对应的在需要用到`Vue`的`html`用`script`导入对应的如下代码

```html
<!-- 开发环境版本，包含了有帮助的命令行警告 -->
<script src="https://cdn.jsdelivr.net/npm/vue@2/dist/vue.js"></script>
```

# 创建一个Vue应用

`Vue.js` 的核心是一个允许采用简洁的模板语法来声明式地将数据渲染进` DOM `的系统：

```html
<div id="app">
    {{ message }}
</div>
```

我们可以`new` 一个`Vue`对象，然后给里面给予参数，以前我们常常用`var`来表明我们的对象，但是我们现在一般更新用`let`(变量）/`const`（常量）来表示我们的对象。

```js
var app = new Vue({})
```

事实上`var`的设计可以看成`JavaScript`语言设计上的错误.但是这种错误多半不能修复和移除,以为需要向后兼容。大概十年前,Brendan Eich就决定修复这个问题,于是他添加了一个新的关键字: `let`.我们可以将`let`看成更完美的`var`

```js
let app = new Vue({ //let(变量）/const（常量）
    el: '#app', //把id=app的这个div传给了Vue这个实例,让我们的Vue去管理他
    data: {
        message: 'Hello Vue!'
    }
})//之所以这个能new Vue因为js内部已经定义了，无需担心
```

# Vue对象的生命周期

在html里面我们常常下面的形式进行对应的定义。

```js
let app = new Vue({ //let(变量）/const（常量）
    el: '#app',
    data: {
        message: 'Hello Vue!'
    }
})
```

但内部并没有这么简单，创造这个`Vue`对象的时候，内部会有一个生命周期。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210324205213585.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1MjIzMTU5NTc0Mg==,size_16,color_FFFFFF,t_70)

每个 `Vue `组件实例在创建时都需要经历一系列的初始化步骤，比如设置好数据侦听，编译模板，挂载实例到 `DOM`，以及在数据改变时更新` DOM`。在此过程中，它也会运行被称为生命周期钩子的函数，让开发者有机会在特定阶段运行自己的代码。

举例来说，`mounted` 钩子可以用来在组件完成初始渲染并创建 `DOM `节点后运行代码：

```js
var app = new Vue({ //let(变量）/const（常量）
    el: '#app',
    data: {
        message: 'Hello Vue!'
    },
    beforeCreate:function(){
        console.log("create");
    },
    mounted:function(){
        console.log("mounted");
    }var app = new Vue({ //let(变量）/const（常量）
    el: '#app',
    data: {
    message: 'Hello Vue!'
},
                  beforeCreate:function(){
    console.log("create");
},
    mounted:function(){
        console.log("mounted");
    }
})
})
```

还有其他一些钩子，会在实例生命周期的不同阶段被调用，最常用的是 [`mounted`](https://cn.vuejs.org/api/options-lifecycle.html#mounted)、[`updated`](https://cn.vuejs.org/api/options-lifecycle.html#updated) 和 [`unmounted`](https://cn.vuejs.org/api/options-lifecycle.html#unmounted)。

所有生命周期钩子函数的 `this` 上下文都会自动指向当前调用它的组件实例。注意：避免用箭头函数来定义生命周期钩子，因为如果这样的话你将无法在函数中通过 `this` 获取组件实例。

# Vue指令

`Vue` 使用一种基于 `HTML` 的模板语法，使我们能够声明式地将其组件实例的数据绑定到呈现的 `DOM `上。所有的` Vue` 模板都是语法层面合法的 `HTML`，可以被符合规范的浏览器和 `HTML `解析器解析。

在底层机制中，`Vue` 会将模板编译成高度优化的 `JavaScript` 代码。结合响应式系统，当应用状态变更时，`Vue` 能够智能地推导出需要重新渲染的组件的最少数量，并应用最少的 `DOM` 操作。

下面将对`vue`的一些基本语法进行介绍。

## 绑定元素el

如上面例子我们一般用`el`来绑定我们对应托管元素的`id`。

```html
<div id="app">
    {{ message }}
</div>
```

```js
var app = new Vue({ //let(变量）/const（常量）
    el: '#app',
    data: {
        message: 'Hello Vue!'
    }
})
```

此时`app`为`id`为`app`的进行了绑定，`message`属性进行了映射。

## 绑定点击click

我们可以对按钮进行点击绑定，由两种绑定方式。

```html
<button v-on:click=" ">-</button>
```

```html
<button @click="add">+</button>
```

第二种方式也叫语法糖绑定。

```html
<div id="app">{{counter}}
    <button v-on:click="add">+</button>
    <button v-on:click="sub">-</button>
</div>
```

```html
<div id="app">{{counter}}
    <button @click="add">+</button>
    <button @click="sub">-</button>
</div>
```

当使用`click`时候会对应一个方法名，来调用我们`js`里面的`methods`。

```js
//let(变量）/const（常量）
const app = new Vue({
    el: '#app',  //把id=app的这个div传给了Vue这个实例,让我们的Vue去管理他
    data: {
        counter: 0,
        message: '你好啊ceit!',
        movies: ['喜欢你', '啊？', '不是吧']
    } ,   //定义数据
    methods:{
        add: function () {
            // counter++;不能在这里写counter，不然他会找全局的counter
            this.counter++;
            console.log("执行了+")
        },
        sub: function () {
            this.counter--;
            console.log("执行了-")
        }
    }
}); 
```

## 循环列表v-for

我们可以在被绑定的对象里面循环我们的数据，快速输出列表中的元素。

```html
<div id="app">
    <ul>
        <li v-for="item in movies">{{item}}</li>
    </ul>
</div>
```

```js
const app = new Vue({
    el: '#app',  
    data: {
        counter: 0,
        message: '你好啊ceit!',
        movies: ['喜欢你', '啊？', '不是吧']
    }    //定义数据

}); 
```

## 数据外置data

在数据量过大的时候，`vue`允许把数据进行外写下面两种形式等价。

```js
const app = new Vue({
    el: '#app',  
    data: {
        counter: 0,
        message: '你好啊ceit!',
        movies: ['喜欢你', '啊？', '不是吧']
    } 
}); 
```

```js
const obj = {
    counter: 0,
    message: '你好啊ceit!',
    movies: ['喜欢你', '啊？', '不是吧']
}  //定义数据


const app = new Vue({
    el: '#app',  
    data:obj
}); 
```

## 逻辑操作mustache

在双括号中可以进行一些简单的逻辑拼接。

```html
<div id="app">
	<h2>{{message1}}</h2>
    <h2>{{message1}},ceit</h2>
    <h2>{{message1 + ' ' + message2}}</h2> <!--拼接中间隔开-->
    <h2>{{message1}} {{message2}}</h2> <!--和上面一样拼接-->
    <h2>{{counter * 2 }}</h2> <!--拼接-->
    <h2>{{status ? ‘succeed’ : ‘failed’}} </h2> 
    <h2>{{add}}</h2>
</div>
```

对应的`js`代码

```js
const app = new Vue({
    el: '#app',  
    data: {
        counter: 0,
        status: true,
        message1: '你好啊ceit!',
        message2: 'emo了'
        movies: ['喜欢你', '啊？', '不是吧']
}
                    }); 
```

## 单次渲染v-once

在某些情况下，我们可能不希望界面随意的跟随改变，这个时候，我们就可以使用一个`Vue`的指令`v-once`，口该指令后面不需要跟任何表达式(`v-for`后面是跟表达式的）。

```html
<div id="app">
    <h2 v-once>{{message}}</h2>
</div>
```

指令表示元素和组件(组件后面才会学习)只渲染一次，不会随着数据的改变而改变。

```js
const app = new Vue({
    el: '#app', 
    data: {
        message: 'ok'
    } 
});  
```

## 添加标签v-html

当我们的数据需要附加`html`的标签时，不能直接添加，需要进行`v-html`。

```html
<div id="app">
	<h2>{{ceit}}</h2>
    <h2 v-html="ceit"></h2>
</div>
```

```js
const app = new Vue({
    el: '#app', 
    data: {
        ceit: '<a href="http://www.baidu.com">百度一下</a>'
    } 
}); 
```

```html
<a href="http://www.baidu.com">百度一下</a>
百度一下<!--带链接-->
```

## 覆盖文本v-text

覆盖原本文本内容，我们不经常使用，并非特别灵活。

```html
<div id="app">
    <h2 v-text="message"></h2>
</div>
```

```js
const app = new Vue({
    el: '#app',  
    data: {
        message: 'ok'
    } 
});  
```

## 跳过编译v-pre

`v-pre`用于跳过这个元素和它子元素的编译过程，用于显示原本的Mustache语法。

```html
<div id="app">
	<h2>{{message}}</h2>  <!--输出ok-->
    <h2 v-pre>{{message}}</h2>  <!--输出{{message}}-->
</div>
```

```js
const app = new Vue({
    el: '#app',  
    data: {
        message: 'ok'
    } 
});  
```

## 同步解析v-cloak

在我们执行过程中，过程是这样的

![image-20211013130614659](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211013130614659.png)

当`js`解析慢的时候，我们的用户会看到原本的`Mustache`语法。为了解决这个情况，我们给我们代理的元素添加一个`v-cloak`属性，不经常用，以后会被模板渲染。

```html
<style>
    [v-cloak]{display:none}
</style>
```

```html
<div id="app" v-cloak> 
	<h2>{{message}}</h2>  <!--输出ok-->
    <h2 v-pre>{{message}}</h2>  <!--输出{{message}}-->
</div>
```

在`vue`解析之前,`div`中有一个属性`v-cloak`，在`vue`解析之后，`div`中没有一个属性`v-cloak`。

```js
const app = new Vue({
    el: '#app', 
    data: {
        message: 'ok'
    } 
});  
```

# 动态绑定v-bind

以京东为例，在京东的首页轮换图是`src`去请求一个`url`，后端返回`json`字符串，我们通过字符串中得到多个`url`，通过这些`url`去请求图片。

前面我们学习的指令主要作用是将值插入到我们模板的内容当中。但是，除了内容需要动态来决定外，某些属性需要动态来绑定。

- 动态绑定a元素的`href`属性。
- 如动态绑定`img`元素的`src`属性这个时候，我们可以使用`v-bind`指令。
  作用︰动态绑定属性，`any (with argument)` | `Object(without argument)`，对应的参数:`attrOrProp (optional)`
- Mustache语法不在标签内使用。

```html
<div id="app">
    <a v-bind:href="imgURL"> </a>
    <img v-bind:src="imgURL">
</div>
```

```js
const app = new Vue({
        el: '#app',  
        data: {
            imgURL:"www.http://img11.360butming.com/mobilecms/......."
        }
    });  
```

这里更加推荐`v-bind`的语法糖。

```html
<div id="app">
    <a :href="imgURL"> </a>
    <img :src="imgURL">
</div>
```

## 动态绑定的对象语法

1. 同样我们可以把`data`的数值动态绑定到`class`里面。

```html
<div id="app">
	<h2 :class="active">电影</h2>
</div>
```

```js
 const app = new Vue({
        el: '#app',  
        data: {
            active: 'active'
        }
    });  
```

2. 通过`boolean`值来判断有没有这个类名

```html
<div id="app">
	<h2 :class="{key1:value1,key2:value2}">电影</h2>  <!--此时这里是对象，我们一般key1是类1，key2是类2，value1是真，value值2是假-->
    <h2 :class="{cat:ture,dog:false}">电影</h2>  <!--此时cat会被绑定，布尔值是true则被绑定-->
    <h2 :class="{cat:iscat,dog:isdog}">电影</h2>  <!--此时cat会被绑定，布尔值是true则被绑定-->
</div>
```

```js
 const app = new Vue({
        el: '#app', 
        data: {
            iscat: 'true'  //控制这里的boolean来控制view层的
            isdog: 'true'
        }
    });  
```

3. 例子：通过按钮控制我们的颜色

```html
<div id="app">
    <h2 class="title" :class="{cat:iscat,dog:isdog}">电影</h2>  <!--我们的属性不会覆盖--> 
    <button v-on:click="btnClick"> 按钮</button>
</div>
```

```html
<div id="app">
    <h2 class="title" :class="getClasses()">电影</h2>  <!--这里的括号不能省略--> 
    <button v-on:click="btnClick"> 按钮</button>  <!--这里的括号能省略--> 
</div>
```

对应下面两个

```js
 const app = new Vue({
        el: '#app', 
        data: {
            iscat: 'true'  //控制这里的boolean来控制view层的
            isdog: 'true'
        }
     	methods:{
     		btnClick:function(){
     this.isActive = !this.isActive}
 }
    });  
```

```js
 const app = new Vue({
        el: '#app', 
        data: {
            iscat: 'true'  //控制这里的boolean来控制view层的
            isdog: 'true'
        }
     	methods:{
     		btnClick:function(){
     this.isActive = !this.isActive
 }
			getClasses:function(){
		return	{cat:this.iscat,dog:this.isdog}  //这里的{}不可以省略
            }
 }
    });  
```

> 我们推荐下面这种写法

## 动态绑定的数值语法

```html
<div id="app">
	<h2 :class="[key1:value1,key2:value2]">电影</h2>  <!--此时这里是数组-->
    <h2 :class="[iscat,isdog]">电影</h2>  <!--这里如果加上单引号就是字符串-->
</div>
```

```js
 const app = new Vue({
        el: '#app', 
        data: {
            iscat: 'true'  //控制这里的boolean来控制view层的
            isdog: 'true'
        }
    });  
```

> 用的很少

## 动态绑定v-for

1. 列表的高亮

点击我们列表哪一项，哪一项变成红色

```html
<style>
  .active{
      color: darkred;
  }
</style>
```

```html
<div id="app">
    <ul>
        <li v-for="(m, index) in movies" :class="{active:currentIndex === index}" @click="liclick(index)">{{m}}</li>
    </ul>
</div>
```

```js
//let(变量）/const（常量）
    const app = new Vue({
        el: '#app',
        data: {
            movies: ['喜欢你', '啊？', '不是吧'],
            currentIndex: -1
        },
        methods:{
            liclick() {
                this.currentIndex = index;
            }
        }
    });
```

### 5.3.1、for遍历对象

假如我们有对象

```js
data:{
    book:
        {name='why',
         price:xx}
}
```

**遍历对象有函数重载的思想**

在遍历对象的过程中只是获取一个值，获取到的是value

```html
<div>
    <ul>
        <li v-for"value in book"></li>
    </ul>
</div>
```

在遍历对象的过程中获取的是key，value

```html
<div>
    <ul>
        <li v-for"(value,key) in book"></li>
    </ul>
</div>
```

在遍历对象的过程中获取key，value和index

```html
<div>
    <ul>
        <li v-for"(value,key,index) in book"></li>
    </ul>
</div>
```

### 5.3.2、for获取数组

```html
data:{
    book:
        ['why',
         'price']
}
```

遍历数组很简单，如下

```html
<div id="app">
  <!--1.在遍历的过程中,没有使用索引值(下标值)-->
  <ul>
    <li v-for="item in names"></li>
  </ul>
  <!--2.在遍历的过程中,获取索引值-->
  <ul>
    <li v-for="(item,index) in names"></li>
  </ul>
</div>
```

### 5.3.3、for获取数组里面的对象

```js
data:{
    books:[
        {....... price:xx}
        {....... price:xx}
        {....... price:xx}
        {....... price:xx}
        {....... price:xx}
    ]
}
```

**常常使用与Json数据联系**

```json
{
    "msg":"处理成功！",
    "code":100,
    "page":{
        "endRow":2,
        "firstPage":1,
        "hasNextPage":true,
        "hasPreviousPage":false,
        "isFirstPage":true,
        "isLastPage":false,
        "lastPage":3,
        "list":[
            {
                "age":18,
                "email":"test1@baomidou.com",
                "id":1,
                "name":"Jone"
            },
            {
                "age":20,
                "email":"test2@baomidou.com",
                "id":2,
                "name":"Jack"
            }
        ],
        "navigateFirstPage":1,
        "navigateLastPage":3,
        "navigatePages":3,
        "navigatepageNums":[
            1,
            2,
            3
        ],
        "nextPage":2,
        "pageNum":1,
        "pageSize":2,
        "pages":3,
        "prePage":0,
        "size":2,
        "startRow":1,
        "total":5
    }
}
```



当我们的数据`data`里面有一个key为`books`的对象，它是数组形式的，数组里面是`book`对象，每个`book`对象里面的有`price`属性，我们的就可以用

`for(let i;i<this.books.length;i++)` this.books[i].price

`for(let i in this.books)` this.books[i].price

**`for(let book of this.books)`  拿到book**

> 我们很推荐这个方式

把里面的`price`统计到一个局部变量里面返回

### 5.3.4 、for和key组件的配合

为了更高效的更新虚拟Dom我们要加`:key`来与遍历的数据进行绑定，在Vue中就相当于链表时插入，否则就是动态数组更新，复杂度很高

### 5.3.5、数组的响应式编程

```html
data:{
    book:
        ['why','price']
}
```

我们只有以下几个能对数组里面的响应编程

```js
push() //添加到最后
pop()  //删除
shift() //删除第一个
unshift() //在数值最前面添加元素


// splice作用:删除元素/插入元素/替换元素
splice()
//下标法下的Start
//删除元素:第二个参数传入你要删除几个元素(如果没有传,就删除后面所有的元素)
//替换元素:第二个参数，表示我们要替换几个元素，后面是用于替换前面的元素
//插入元素：删除元素是0，后面是我们要插入的元素

sort() //排序，小到大
reverse() //反转
Vue.set(){this.数组(要修改的对象),索引值，修改后的值}

this.book.XX方法
```

在计算和的方法中，我们可以用到定义一个函数

```js
function sum(...num){ //...num有什么用
}
```

所有的形参都放进一个数组里面，**我们把这种写法叫可变参数**

**当我们靠索引改变数组不是响应式！！！**

## 动态绑定v-style

我们可以封装一个单独的组件，他是可复用的

比如我们的京东搜索框，我们可以看到不同页面下的搜索框不一样但有共同点，我们可以根据自定义我们的style来实现完美复用

```html
<div id="app">
	<h2 :style="{key(属性名):value(属性值)}">{{message}}</h2>
    <h2 :style="{fontSize: '50px'}">{{message}}</h2> <!--key只会被当成字符串，value不加的话会被当成变量-->
</div>
```

我们动态时候

```html
<div id="app">
<!--    <h2 :style="{key(属性名):value(属性值)}">{{message}}</h2>-->
    <h2 :style="{fontSize: max}">{{message}}</h2> 
</div>
```

```js
    //let(变量）/const（常量）
    const app = new Vue({
        el: '#app',
        data: {
            message:"ceit",
            max: '50px'// 此时这里加''
        }
    });
```

我们所有的对象都可以抽取到methods里面再return

# 6、计算属性

## 6.1、计算属性的普通运算

但是在某些情况，我们可能需要对数据进行一些转化后再显示，或者需要将多个数据结合起来进行显示口比如我们有firstName和lastName两个变量，我们需要显示完整的名称。但是如果多个地方都需要显示完整的名称，我们就需要写多个{{firstName} {last Name}}

当我们有大量的{{a}}{{b}}进行运算的时候，我们即使运用函数的方法，展示的view图也非常复杂，因从我们在`Vue`里面增添了一个新的叫`computed`的属性，里面是一个对象`{}`

```html
<div id="app">
    <h2>{{fullname}}</h2>   <!--这就不用加（）号哦-->
</div>
```

```js
    const app = new Vue({
        el: '#app',
        data: {
            firstname: '???',
            lastname: '!!!'
        },
        computed:{
            fullname: function () {
                return this.firstname+this.lastname;
            }
        }
    });
```

## 6.2、计算属性的复杂运算

当我们的数据里面有一个`books`数值里面是`book`对象，每个`book`对象里面的有`price`属性，我们的就可以用

`for(let i;i<this.books.length;i++)`

`for(let i in this.books)`

`for(let book of this.books)`  拿到book

> 我们很推荐这个方式

把里面的`price`统计到一个局部变量里面返回

## 6.3、计算setter和getter

我们来结束为什么我们可以直接使用fullname

实际中在computed里面的fullname是一个对象，对象里面有两个方法分别是`set`和`get`方法

但是我们的计算属性几乎没有`set`方法，是一个只读属性，所有我们直接进化成

```js
        computed:{
            fullname: function () {
                return this.firstname+this.lastname;
            }
```

> 对字符串分割.split(' ') 即`const names = Value.split(' ')` 放回用数值形式改data里面的值

我们就算写set方法也不用写上`( )`

## 6.4、计算属性和methods的对比

我们推荐使用在计算时候使用我们的计算实现，经过对比，我们明显发现

当我们同时使用我们的计算属性和method时候

**我们的计算属性只调用一次然后就进入缓存，而函数会一直调用**

# 7、块级作用域

## 7.1、什么是块级作用域

**在ES5的时候：**

JS中使用var来声明一个变量时,变量的作用域主要是和函数的定义有关.

针对于其他块定义来说是没有作用域的，比如if/for等，这在我们开发中往往会引起一些问题。

- 在if作用域中假如我们的变量没有块级作用域，则我们可在if外对变量进行直接更改
- 在for作用域中假如我们的变量没有块级作用域，则我们可以在for外对变量修改

我们是如何解决问题的呢

```js
function(i){
    ....
}(i)
```

我们利用闭包的方法引进函数解决我们的块作用域

**在ES6的时候：**

引进let和const，let完全取代了Var

## 7.2、const的使用和注意

- 在很多语言中已经存在,比如C/C++中,主要的作用是将某个变量修饰为常量.在JavaScript中也是如此,使用const修饰的标识符为常量,不可以再次赋值.什么时候使用const呢?
- 当我们修饰的标识符不会被再次赋值时,就可以使用const来保证数据的安全性.
- **我们使用const修饰的时候我们要进行赋值**
- **常量的含义是指向的对象不能修改，但是可以改变对象内部的属性**

> 为什么能改变内部的属性

![image-20211013175324906](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211013175324906.png)

- **在开发中我们优先使用const，只有需要改变某一个标识符的时候才使用let**

# 8、ES版本变化

## 8.1、属性的增强写法

```js
const name = 'why';
const age = 18;
const height = 1.88

//ES5的写法
const obj={
    name: name,
    age: age,
    height: height}

//ES6的写法
const obj = {
    name,
    age,
    height
}
```

## 8.2、函数的增强写法

```js
//ES5的写法
const obj = {
    run: function () {

    },
    eat: function (){

    }
}
//ES6的写法
const obj = {
    run() {

    },
    eat() {

    }
}
```

# 9、事件监听

在前端开发中，我们需要经常和用于交互。

这个时候，我们就必须监听用户发生的时间，比如点击、拖拽、键盘事件等等在Vue中如何监听事件呢?使用v-on指令

> 我们和v-bind一样使用语法糖`:`使用语法糖`@`

在事件监听的时候

- 如果方法不需要参数则方法后面的()可以不添加
  - 如果方法本身有一个参数，那么会默认把原生事件event参数传递进去，在事件定义时，写方法时省略了小括号，但是方法本身是需要一个参数的，这个时候，vue会默认将浏览器生产的event事件对象作为参数传入到方法。

```html
<div id="app">
  <button @click="btnClick">按钮</button>
</div>
```

```js
const app = new Vue({
  el: '#app',
  methods: {
    btnClick(a){
      console.log('?',a)
    }
  }
})
```

![image-20211013183622106](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211013183622106.png)

- 如果需要同时传入某个参数，同时需要event，可以通过$event传入事件

```html
<div id="app">
  <button @click="btnClick(123,$event)">按钮</button>  <!--这里我们的要是写abc就被看做对象-->
</div>
```

```js
const app = new Vue({
  el: '#app',
  methods: {
    btn3Click(a,event){
    }
  }
})
```

## 9.1、v-on修饰符

在某些情况下，我们拿到event的目的可能是进行一些事件处理。

Vue提供了修饰符来帮助我们方便的处理一些事件:.

- `.stop` 调用`event.stopPropagation()`

> 我们的两个对象有嵌套关系，我们在内层设置`.stop`

- `.prevent` 调用`event.preventDefault)`。

> 我们不想要表单的提交，转按钮为input，设置`@click.prevent=“方法”`，把要提交的东西传进方法自己搜集数据再发送请求

- `.{(keyCode | keyAlias}` 只当事件是从特定键触发时才触发回调。

> 用**@keyup.我们要监听的事件=''方法 "**，比如回车`@keyup.enter=""`等等

- `.native`  监听组件根元素的原生事件。

> 比如我们自定义一个组件我们想监听则必须`@click.native`

- `.once`  只触发一次回调。

> 希望用户第一次点有反应，后面点都没反应

## 9.2、判断

判断的时候

- 我们的`v-if`和`v-else`可以不在一个标签内，遵循最近原则
- 要是`v-if`里面还有子标签，`if`要是不对，我们子标签直接随之消失

```html
<div id="app">
  <h2 v-if="score>=90">优秀</h2>
  <h2 v-else-if="score>=80">良好</h2>
  <h2 v-else-if="score>=60">及格</h2>
  <h2 v-else>不及格</h2>
</div>
```

`v-if`和`v-show`对比

- `v-if`当条件为false时，压根不会有对应的元素在DOM中。

- `v-show`当条件为false时，仅仅是将元素的display属性设置为none而已。



## 9.3、登入切换小功能

小问题

- 如果我们在有输入内容的情况下，切换了类型，我们会发现文字依然显示之前的输入的内容。但是按道理讲，我们应该切换到另外一个input元素中了。在另一个input元素中，我们并没有输入内容。

为什么会出现这个问题呢?

- 这是因为Vue在进行DOM渲染时，出于性能考虑，会尽可能的复用已经存在的元素，而不是重新创建新的元素。在上面的案例中，Vue内部会发现原来的input元素不再使用，直接作为else中的input来使用了。

解决方案∶

- 如果我们不希望Vue出现类似重复利用的问题，**可以给对应的input添加key并且我们需要保证key的不同**

![image-20211013194009975](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211013194009975.png)

**Vue尽量可能进行复用**

```html
<div id="app">
  <span v-if=isUser>
    <label for="username">用户账号</label>
    <input type="text" id="username" placeholder="用户账号" key="username">
    </span>
  <span v-else>
    <label for="email">用户邮箱</label>
    <input type="text" id="email" placeholder="用户邮箱" key="email">
  </span>
  <button @click="isUser = !isUser">切换类型</button>
</div>
```

```js
 const app = new Vue({
    el: '#app',
    data: {
      isUser: true
    }
  })
```

# 10、购物车案例(项目)

要求我们的购物车有以下功能：

- 我们的购买数量可以增加或者减少
- 点击移出的时候我们能把对应的行去掉
- 下面有对应的总价显示

```html
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" href="style.css">

</head>
<body>
<div id="app">
  <div v-if="books.length">
  <table>
    <thead>
    <tr>
      <td></td>
      <td>书籍名称</td>
      <td>出版日期</td>
      <td>价格</td>
      <td>购买数量</td>
      <td>
        操作
      </td>
    </tr>
    </thead>
    <tbody>
    <tr v-for="(items,index) in books">
      <td>{{items.id}}</td>
      <td>{{items.name}}</td>
      <td>{{items.date}}</td>
      <td>{{items.price | showPrice}}</td>
      <td>
        <button @click="increment(index)">+</button>
        {{items.count}}
        <button @click="decrement(index)" :disabled="items.count<=1" >-</button>
      </td>
      <td>
        <button @click="removeHandler">移出</button>
      </td>
    </tr>
    </tbody>
  </table>
  <h2>总价格:{{total|showPrice}}</h2>
  </div>
  <h2 v-else>购物车为空</h2>
</div>
<script src="https://cdn.jsdelivr.net/npm/vue@2.6.14/dist/vue.js"></script>
<script src="main.js"></script>

</body>
</html>
```

```css
table {
    border: 1px solid #e9e9e9;
    border-collapse: collapse;
    border-spacing: 0;
}
th, td {
    padding: 8px 16px;
    border: 1px solid #e9e9e9;
    text-align: left;
}
th {
    background-color: #f7f7f7;
    color: #5c6b77;
    font-weight: 600;
}
```

```js
const app = new Vue({
  el: '#app',
  data: {
    books: [{
      id: 1,
      name: '《算法导论》', date: '2006-3',
      price: 85.00, count: 1
    },
      {
        id: 2,
        name: '《UN工X编程艺术》 ', date: '2006-2 ',
        price: 59.00, count: 1
      },
      {
        id: 3,
        name: '《编程珠现》', date: '2008-10',
        price: 39.00, count: 1
      },
      {
        id: 9, name: '《代码大全》', date: '2006-3',
        price: 128.00, count: 1
      },
    ]
  },
  methods:{
    // getFinalPrice(price){
    //   return '￥' + price.toFixed(2);
    // }
    increment(index){
      this.books[index].count++;
    },
    decrement(index){
      this.books[index].count--;
    },
    removeHandler(index){
      this.books.splice(index,1,);
    }
  },
  computed:{
    total(){
            return this.books.reduce((preValue, book) => preValue + book.price * book.count,0)
  },
  filters:{
    showPrice(price){
      return '￥' + price.toFixed(2);
    }
  }
})
```

# 11、JavaScript高阶用法

编程范式：

- 命令式编程/声明式编程
- 面向对象编程（第一公民：对象）/函数式编程（第一公民：函数）

以前

```js
const nums = [10, 20, 30, 50, 111, 222, 333, 25, 17]
//1.取出所有小于100的数字
let newnums = []
for (let n of nums) {
    if (n < 100) {
        newnums.push(n);
    }
}
//2.将所有小于100的数字进行转换：*2
let newnums2 = []
for (let n of newnums) {
    newnums2.push(n * 2);
}
//3.将所有newNums希昂加，得到最后的结果
let total = 0;
for (let n of newnums2) {
    total += n
}
```

## 11.1、filter

回调函数，会把nums传进来，filter的回调函数要一个`boolean`

- true时，函数内部自动把这次回调的n加入到新的数组中
- false时，当返回false时，函数内部会过滤掉这次n

```js
let newNums = nums.filter(function (n) {
    return n<100
})
```

## 11.2、Map

回调函数，会把nums传进来，经过处理返回一个新的值

```js
let newNums = nums.map(function (n) {
    return n*2
})
```

## 11.3、reduce

reduce作用对数组中所有的内容进行汇总

```js
let total = nums.reduce(function (preValue,n) {
    return preValue+n;
},0)
```

## 11.4 增强写法

因从我们上面的写法可以化简

```js 
let total = nums.filter(function (n) {
    return n<100;
}).map(function (n) {
    return n*2;
}).reduce(function (preValue,n) {
    return preValue + n;
},0)
```

**但是我们不喜欢这种，我们可以写的更简单**

```js
let total = nums.filter(n=>n<100).map(n=>n*2).reduce((pre,n)=>pre+n);
```

> 非常推荐

# 12、v-model

表单绑定，我们往往用双向绑定来进行表单数据

```html
<div id="app">
  <input type="text" v-model="message">
  {{message}}
</div>
```

```js
var app = new Vue({
    el: '#app',
    data: {
        message: 'Hello Vue!'
    }
})
```

## 12.1、为什么我们能实现双向绑定

其实我们的v-model相当于

```html
  <input type="text" :value="message" @input="message = $event.target.value"> 
```

```js
var app = new Vue({
    el: '#app',
    data: {
        message: 'Hello Vue!'
    }
})
```

> 我们推荐使用v-model

## 12.2、单选框的radio

```html
<div id="app">
  <label for="male">
    <input type="radio" id="male"  value="男" v-model="sex">男
  </label>
  <label for="female">
    <input type="radio" id="female"  value="女" v-model="sex">女
  </label>
  <h2>你选择的性别是:{{sex}}</h2>
</div>
```

```js
  var app = new Vue({
    el: '#app',
    data: {
      message: 'Hello Vue!',
      sex: '男'
    }
  })
```

## 12.3、单，多选框的ckeckbox

单选框

```html 
<div id="app">
  <label for="agree">
    <input type="checkbox" id="agree" v-model="isAgree">同意协议
  </label>
  <h2>你选择的是：{{isAgree}}</h2>
  <button :disabled="!isAgree">下一步</button>
</div>
```

```js
  var app = new Vue({
    el: '#app',
    data: {
      message: 'Hello Vue!',
      sex: '男',
      isAgree:false
    }
  })
```

多选框

```html
<div id="app">
    <input type="checkbox" value="篮球" v-model="hobbies">篮球
    <input type="checkbox" value="足球" v-model="hobbies">足球
    <input type="checkbox" value="乒乓球" v-model="hobbies">乒乓球
    <input type="checkbox" value="烂球" v-model="hobbies">烂球
  <h2>你选择的是：{{hobbies}}</h2>
<!--  <button :disabled="!isAgree">下一步</button>-->
</div>
```

```js
  var app = new Vue({
    el: '#app',
    data: {
      message: 'Hello Vue!',
      sex: '男',
      isAgree: false, //单选框
      hobbies:[] //多选框
    }
  })
```

可是我们一般在选择的时候不是这样写的，我们一般动态绑定我们的值内容的

```html
<div id="app">
  <label v-for="item in originHobbies" :for="item">
  <input type="checkbox" :value="item" :id="item" v-model="hobbies">{{item}}</label>
</div>
```

我们为了用户放别每一个都配置一个label

```js
  var app = new Vue({
    el: '#app',
    data: {
      message: 'Hello Vue!',
      hobbies: [],
      originHobbies:['篮球','足球','乒乓球','羽毛球','台球','高尔夫球']  //这里一般是服务器给我们的json里面的
  }
  })
```

对应的 originHobbies也是对应的

## 12.4、select

单选

```html
<div id="app">
  <select id="" v-model="fruit">
    <option value="苹果"  >苹果</option>
    <option value="香蕉"  >香蕉</option>
    <option value="栗子"  >栗子</option>
    <option value="荔枝"  >荔枝</option>
    <option value="西瓜"  >西瓜</option>
  </select>
  <h3>你选择的是{{fruit}}</h3>
</div>
```

```js
  var app = new Vue({
    el: '#app',
    data: {
      message: 'Hello Vue!',
      fruit: '香蕉'
    }
  })
```

多选

```html
<div id="app">
  <select id="" v-model="fruit"  multiple>
    <option value="苹果"  >苹果</option>
    <option value="香蕉"  >香蕉</option>
    <option value="栗子"  >栗子</option>
    <option value="荔枝"  >荔枝</option>
    <option value="西瓜"  >西瓜</option>
  </select>
  <h3>你选择的是{{fruit}}</h3>
</div>
```

```js
 var app = new Vue({
    el: '#app',
    data: {
      message: 'Hello Vue!',
      fruit: []
    }
  })
```

## 12.5、修饰符

### 1、lazy

在`v-model`后面加上`.lazy`时候我们就不会出现只有输入完成，敲下回车/失去焦点的时候，输入框此次才发生绑定机制

### 2、number

我们在`input`输入的类型都是string类型的，我们想要和数据中data绑定变成int型时候，我们可以在在`v-model`后面加上`.number`就是number类型

### 3、trim

我们可以在在`v-model`后面加上`.trim`来去掉输入字符前的空格

# 13、组件化

组件化的思想︰

- 如果我们将一个页面中所有的处理逻辑全部放在一起，处理起来就会变得非常复杂，而且不利于后续的管理以及扩展。
- 但如果，我们讲一个页面拆分成一个个小的功能块，每个功能块完成属于自己这部分独立的功能，那么之后整个页面的管理和维护就变得非常容易了。

![image-20211014192401122](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211014192401122.png)

组件化思想的应用:

- 有了组件化的思想，我们在之后的开发中就要充分的利用它。
- 尽可能的将页面拆分成一个个小的、可复用的组件。
- 这样让我们的代码更加方便组织和管理，并且扩展性也更强。

<template>里面东西过多的时候，我们要用div作为root目录

## 13.1、组件的使用

分为三个步骤：

- 创建组件构造器

- 注册组件

- 使用组件

![image-20211014192715812](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211014192715812.png)

## 13.2、组件化的实现

有了组件化以后我们都不需要用到thymleaf的共同功能，只用把我们共同部分进行抽取，最后利用起来就好

在ES6引进了``来，功能更加强大，可以更方便的换行

```js
// 定义一个名为 button-counter 的新组件
Vue.component('button-counter', {
  data: function () {
    return {
      count: 0
    }
  },
  template: '<button v-on:click="count++">You clicked me {{ count }} times.</button>'
})
  var app = new Vue({  
    el: '#app',
    data: {
      message: 'Hello Vue!',
      fruit: '香蕉'
    }
  })
```

**注意我们要利用组件时候要写在被托管在Vue里面的dom对象才能生效，不然是无法使用我们的组件的的**

如果我们的dom元素我们不需要添加我们的操作但是我们想让我们的标签生效，我们可以写

```js
new Vue({ el: '#components-demo' })
```

我们在在设计页面的时候，我们可以写一个专门的js来注册我们对应的组件，和绑定我们的dom元素

- 在进行页面设计的时候，我们的共同id可以写成一致的接口形式来配对，比如菜单上是对应的menu之类的

要是我们想要我们的局部组件

```js
  var app = new Vue({  
    el: '#app',
    data: {
      message: 'Hello Vue!',
      fruit: '香蕉'
    }
    components:{
      组件使用名: 组件名定义名
  }  
  })
```

我们在开发时候我们会使用我们的局部主键

## 13.3、父子组件

根据上面的方式我们可以套娃创建父子组件

```html
<div id="app">
  <cpn2></cpn2>
</div>
```

```js
const cpnC1 = Vue.extend({
    template: `
    <div>
      <p>晚上</p>
      <p>什么鬼</p>
    </div> `
  })
  const cpnC2 = Vue.extend({
    template: `
    <div>
      <p>晚上</p>
      <cpn1></cpn1>
    </div> `,
    components:{
      cpn1:cpnC1
    }
  })
const app = new Vue({
  el:'#app',
  components:{
    cpn2:cpnC2
  }
})
```

其实Vue实例也可以看作一个组件，是最顶层的组件，我们也叫它root

注意我们的app里面不可以写cpn1哦

在编译的时候我们在面对不认识的标签的时候，我们会被替换掉，从局部组件到全局组件的顺序开始寻找

## 13.4、组件的语法糖

全局

```js
// 定义一个名为 button-counter 的新组件
Vue.component('button-counter', {
  data: function () {  //这里必须是一个function，里面的写法和Vue对象里面的写法一致，而且这是有一个函数哦，它是只能在这个组件里面使用，你也可以使用它的增强写法
    return {
      count: 0
    }
  },
  template: '<button v-on:click="count++">You clicked me {{ count }} times.</button>'
})
```

局部

```js
  var app = new Vue({  
    el: '#app',
    data: {
      message: 'Hello Vue!',
      fruit: '香蕉'
    }
    components:{
      'cpn2': {
        template: '<button v-on:click="count++">You clicked me {{ count }} times.</button>'
  }
  }  
  })
```

## 13.5、组件的抽离写法

```html
<div id="app">
  <cpn></cpn>
</div>
```

```html
<template id="test">
  <div>
    <h2>dasda</h2>
    <p>dasdasd</p>
  </div>
</template>
<script type="text/x-template" id="cpn">
  <div>
    <h2>dasda</h2>
    <p>dasdasd</p>
  </div>
</script>
```

```js
Vue.component('cpn',{
  template: '#cpn'
})
new Vue({el:'#app'})
```

我们这里按照视频进行实验时候发现我们爆红，虽然能正常运行，请在文档纠正时候进行修改

# 14、组件的通信

在上一个小节中，我们提到了子组件是不能引用父组件或者Vue实例的数据的。但是，在开发中，往往一些数据确实需要从上层传递到下层∶

- 比如在一个页面中，我们从服务器请求到了很多的数据。
- 其中一部分数据，并非是我们整个页面的大组件来展示的，而是需要下面的子组件进行展示。
- 这个时候，并不会让子组件再次发送一个网络请求，而是直接让大组件(父组件)将数据传递给小组件(子组件)。

如何进行父子组件间的通信呢?

- 通过props向子组件传递数据
- 通过事件向父组件发送消息

![image-20211014225809613](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211014225809613.png)

## 14.1、props

在组件中，使用选项props来声明需要从父级接收到的数据。props的值有两种方式︰

- 字符串数组，数组中的字符串就是传递时的名称。
- 对象，对象可以设置传递时的类型，也可以设置默认值等。

```html
<div id="app">
  <cpn :cmovies="movies" :cmessage="message"></cpn>
</div>
<template id="cpn">
  <div>
    <p>{{cmovies}}</p>
    <h2>{{cmessage}}</h2>
  </div>
</template>
```

```js
const name= 'name'
const obj={
  name
}
```

```js
const cpn ={
    template:'#cpn',
    props: ['cmovies','cmessage'],
    data() {
      return{}
    },
    methods: {
    }
  }
const app= new Vue({
    el: '#app',
    data: {
        message: '你好啊',
        movies:['海王','海贼王','海尔兄弟']},
    components: {
        cpn
    }})
```

我们也可以指定类型，指定默认值

```js
const cpn ={
    template:'#cpn',
    props: {
      // cmovies: Array,
      // cmessage: String
		//类型是对象或者数组时候，我们的默认值必须是一个函数！！！ default(){return []/{}}
      cmovies:{
        type: String,
        default: "aaaa"  //没有值就会传默认值
        required:true  //说明这个值是必须传的值
      }
    },
    data() {
      return{}
    },
    methods: {
    }
  }
const app= new Vue({
    el: '#app',
    data: {
        message: '你好啊',
        movies:['海王','海贼王','海尔兄弟']},
    components: {
        cpn
    }})
```

我们也可以自定义类型

```js
function Person(firstName,lastName){
    this.firstName = firstName;
    this.lastName = lastName;
}
```

**注意了，我们的props不支持驼峰，当我们使用驼峰写法的时候，我们在组件绑定的时候，大写改成-小写**

## 14.2、子组件数据转回大组件

![image-20211014235523316](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211014235523316.png)

我们Vue为了复用，常常把一个页面分割成很多部分，进行复用

整个页面（大组件）来请求数据，再把数据分给小组件，当我们点击小组件的时候，小组件会发送一些事件，告诉大组件发送了什么事件，对应点击的是谁，我们的大组件会收到，发送到服务器，请求到另一轮的数据，我们的页面会部分刷新，

```html
<div id="app">
 <cpn @item-click="cpnClick"></cpn>
</div>
<template id="cpn">
  <div>
      <button v-for="item in categories" @click="itemClick(item.id)">{{item.name}}</button>
  </div>
</template>
```

```js
const cpn ={
    template:'#cpn',
    data() {
      return{
        categories:[
          {id:'aaa',name:'热门推荐'},
          {id:'bbb',name:'家电推荐'},
          {id:'ccc',name:'电脑办公'},
          {id:'ddd',name:'手机数码'},
        ]
      }
    },
    methods: {
      itemClick(item){
        this.$emit('item-click',item)
      }
    }
  }
  const app= new Vue({
    el: '#app',
    data: {
      message: '你好啊',
      movies:['海王','海贼王','海尔兄弟']},
    methods:{
      cpnClick(item){
        console.log(item);
      }
    },
  components: {
    cpn
  }})
```

## 14.3、父子组件的双向绑定

```html
<div id="app">
 <cpn :number1="num1" :number2="num2" @numb1change="num1change" @numb2change="num2change"></cpn>
</div>


<template id="cpn">
  <div>
      <h2>{{number1}}</h2>
      <h2>{{dnumber1}}</h2>
<!--      <input type="text" :v-model="dnumber1">-->
      <input type="text" :value="dnumber1" @input="num1Input">
      <h2>{{number2}}</h2>
      <h2>{{dnumber2}}</h2>
<!--      <input type="text" :v-model="dnumber2">-->
      <input type="text" :value="dnumber2" @input="num2Input">
      <h2></h2>
  </div>
</template>
```

```js
 const app= new Vue({
    el: '#app',
    data: {
      num1: 1,
      num2: 0},
    methods: {
      num1change(value){
        this.num1 = parseInt(value)
      },
      num2change(value){
        this.num2=parseInt(value)
      }
    },
  components: {
    cpn:{
      template:'#cpn',
      props:{
        number1: Number,
        number2: Number
      },
      data() {
        return{
            dnumber1:this.number1,
            dnumber2:this.number2
        }
      },
      methods:{
        num1Input(event){
          this.dnumber1=event.target.value;
          this.$emit('numb1change',this.dnumber1)
        },
        num2Input(event){
          this.dnumber2=event.target.value
          this.$emit('numb2change',this.dnumber2)
        }
      }

    }
  }})

```

**扩展**

```html
<div id="app">
 <cpn :number1="num1" :number2="num2" @numb1change="num1change" @numb2change="num2change"></cpn>
</div>


<template id="cpn">
  <div>
      <h2>{{number1}}</h2>
      <h2>{{dnumber1}}</h2>
<input type="text" :v-model="dnumber1">

      <h2>{{number2}}</h2>
      <h2>{{dnumber2}}</h2>
<input type="text" :v-model="dnumber2">

      <h2></h2>
  </div>
</template>
```



```js
 const app= new Vue({
    el: '#app',
    data: {
      num1: 1,
      num2: 0},
    methods: {
      num1change(value){
        this.num1 = parseInt(value)
      },
      num2change(value){
        this.num2=parseInt(value)
      }
    },
  components: {
    cpn:{
      template:'#cpn',
      props:{
        number1: Number,
        number2: Number
      },
      data() {
        return{
            dnumber1:this.number1,
            dnumber2:this.number2
        }
      },
      watch:{
       dnumber1(newValue){
          this.dnumber1=newValue;
          this.$emit('numb1change',this.dnumber1)
        },
       dnumber2(newValue){
          this.dnumber2=newValue;
          this.$emit('numb2change',this.dnumber2)
        }
          //监听谁的值我们用谁命名
      }

    }
  }})
```

## 14.4、父子组件的访问方法

### 1、$children

我们的父组件可能里面有很多子组件

```html
<div id="app">
    <button @click="btnClick">按钮</button>
 <cpn/>
</div>
<template id="cpn">
  <div>
      <h2>我是子组件</h2>
  </div>
</template>
```

```js
  const app= new Vue({
    el: '#app',
    data: {
      num1: 1,
      num2: 0},
    methods: {
    btnClick(){
      console.log(this.$children);
      for(let i of this.$children){
        i.showMessage();
      }
    }
    },
  components: {
    cpn:{
      template:'#cpn',
      methods:{
       showMessage(){
         console.log('Qqqqqq');
       }
      }

    }
  }})
```

> 但是我们很少用

```html
<div id="app">
    <button @click="btnClick">按钮</button>
 	<cpn ref="aaa"/>
    <cpn/>
    <cpn/>
</div>
<template id="cpn">
  <div>
      <h2>我是子组件</h2>
  </div>
</template>
```

```js
  const app= new Vue({
    el: '#app',
    data: {
      num1: 1,
      num2: 0},
    methods: {
    btnClick(){
      this.$refs.aaa.showMessage() //refs是对象类型，默认是空的对象
      }
    }
    },
  components: {
    cpn:{
      template:'#cpn',
      methods:{
       showMessage(){
         console.log('Qqqqqq');
       }
      }

    }
  }})
```



### 2、$parent

与上面同理，但是方法在子组件里面写

# 16、模块化开发

## 16.1、JavaScript功能

在网页开发的早期，js制作作为一种脚本语言，做一些简单的表单验证或动画实现等，那个时候代码还是很少的。

那个时候的代码是怎么写的呢?直接将代码写在<script>标签中即可随着ajax异步请求的出现，慢慢形成了前后端的分离

客户端需要完成的事情越来越多，代码量也是与日俱增。为了应对代码量的剧增，我们通常会将代码组织在多个js文件中，进行维护。

但是这种维护方式，依然不能避免一些灾难性的问题。

## 16.2、为什么要有模块化

我们的项目开发的时候分为多个人，每个人写自己的js，当我们在最后进行整合的时候，会把各自的js导入，但是假如我们的设置的有些变量是重复的，就会导致前端的结构混乱，获得的值混乱，导致界面出现崩溃，因从我们在发展的最后进行了模块化

另外，这种代码的编写方式对js文件的依赖顺序几买是强制性的

- 但是当js文件过多，比如有几十个的时候，弄清楚它们的顺序是一件比较同时的事情。
- 而且即使你弄清楚顺序了，也不能避免上面出现的这种尴尬问题的发生。

就算通过命名闭包解决了命名冲突，但是会导致我们的代码不可复用

我们可以使用将需要暴露到外面的变量，使用一个模块作为出口

- 我们做了什么事情呢?
  - 非常简单，在匿名函数内部，定义一个对象。
  - 给对象添加各种需要暴露到外面的属性和方法(不需要暴露的直接定义即可)。最后将这个对象返回，并且在外面使用了一个MoudleA接受。

- 接下来，我们在man.,js中怎么使用呢?
  - 我们只需要使用属于自己模块的属性和方法即可
  - 这就是模块最基础的封装，事实上模块的封装还有很多高级的话题︰
  - 但是我们这里就是要认识一下为什么需要模块，以及模块的原始雏形。

幸运的是，前端模块化开发已经有了很多既有的规范，以及对应的实现方案。

常见的模块化规范∶

- CommonJS、AMD、CMD，也有ES6的Modules

## 16.3、CommonJS（文件的导入导出）

### 1、配置

### 2、导出

1. 在exports里面定义导出

```js
module.exports ={
    flag: true,
    test(a,b){
        return a+b
    }
    demo(a,b){
        return a*b
    }
}
```

2. 直接在外面定义好，放进exports

### 3、导入

```js
let{test,demo,flag} =require('文件名.js')  //直接把对象解析出来
```

## 16.4、ES6模块化

要在<script>里面命令type="module"

### 1、export导出

我们可以导出函数，判断，类

```js
function sum(a,b){
    return a+b
}
```

```js
if(flag){
    console.log(sum(20,30))
}
```

导出写法有两种

```js
export{
test,demo,flag
}
```

```js
export var num=1000
export function mul(x,y){
    return x*y
}
export class Person{
    run(){
        console.log('222')
    }
}
```

### 2、import导入

```js
import{flag} from "文件名.js"
import 自定义名字 from "文件名.js"
import * as 自定义名字 from "文件名.js"
```

export default 可以在导出的地方来修改导入的命名

此时import可以去除括号的形式，**但是我们默认只能有一个default**

# 17、webpack

什么是webpack 

- 这个webpack还真不是一两句话可以说清楚的。
- 我们先看看官方的解释︰
  At its core, webpack is a static module bundler for modern JavaScript applications.

- 从本质上来讲，webpack是一个现代的JavaScript应用的**静态模块打包**工具。
- CommonJS、AMD、CMD的支持模块化

但是它是什么呢?用概念解释概念，还是不清晰。

- 我们从两个点来解释上面这句话:**模块和打包**

## 17.1、模块

而webpack其中一个核心就是让我们可能进行模块化开发，并且会帮助我们处理模块间的依赖关系。

而且不仅仅是JavaScript文件，我们的CSS、图片、json文件等等在webpack中都可以被当做模块来使用（在后续我们会看到)。

这就是webpack中模块化的概念。

## 17.2、打包

打包如何理解呢?

- 理解了webpack可以帮助我们进行模块化，并且处理模块间的各种复杂关系后，打包的概念就非常好理解了。
- 就是将webpack中的各种资源模块进行打包合并成一个或多个包(Bundle)。
- 并且在打包的过程中，还可以对资源进行处理，比如压缩图片，将scss转成css，将ES6语法转成ES5语法，将TypeScript转成JavaScript等等操作。
- 但是打包的操作似乎grunt/gulp也可以帮助我们完成，它们有什么不同呢?

![image-20211015200725284](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211015200725284.png)

## 17.3、项目初始搭建

我们进行前后端开发的时候进行分离，最后打包到统一的js上面进行总和。

在前端我们进行前端的编辑，创建如下的文件夹

```txt
dist
	bundle.js
src
	-css
		...
	-img
		...
	-js
		...
	-Vue
		...
main.js
index.html
```

我们把对应的文件引入main.js并打包

```js
const {add,mul} =require('./js/MathUtils.js')

console.log(add(20,30));
console.log(mul(20,30));

import {name,age,height} from "./js/info";
console.log(name);
console.log(age);
console.log(height);


require('./css/normal.css')

require('./css/special.less')
document.writeln('<h2>你好的</h2>')


import Vue from 'vue'
import App from "./Vue/App.vue";
new Vue({
  el:'#app',
  template: '<App/>', //替换
  components:{
    App
  }
})
```

CSS中的normal.css和special.less

```css
body{
    /*background-color: antiquewhite;*/
    background: url("../img/1.png");
}
```

```less
@fontSize:50px;
@fontColor:orange;
body{
  font-size: @fontSize;
  color: @fontColor;
}
```

js中的info.js和MathUtils.js

```js
export const name='why';
export const age=18;
export const height =1.88;
```

```js
function add(x,y) {
  return x+y;
}
function mul(x,y) {
  return x*y;
}
module.exports = {
  add,
  mul
}
```

其中Vue涉及到17.4的内容,image直接引进不作配置

同时我们要创建webpack.config.js,这里都是固定的写法

```js
const path = require('path')  

module.exports = {
  entry: './src/main.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
    publicPath:'dist/'
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      },
      {
        test: /\.less$/,
        use: [{
          loader: "style-loader" // creates style nodes from JS strings
        }, {
          loader: "css-loader" // translates CSS into CommonJS
        }, {
          loader: "less-loader" // compiles Less to CSS
        }
        ]
      },
      {
        test: /\.(png|jpg|gif)$/,
        use: [
          {
            loader: 'file-loader',
            options: {
              name: 'img/[name].[hash:8].[ext]'
            },

          }
        ]
      },
      {
        test: /\.vue$/,
        use:['vue-loader']
      }]
  },
  resolve:{
    alias:{
      'vue$':'vue/dist/vue.esm.js'  //设置为runtime-complier
    }
  }
}
```

同时`npm init`初始化得到文件`package.json`

```json
{
  "name": "meetwebpack",
  "version": "1.0.0",
  "description": "",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build": "webpack"  //脚本,生成后唯一要改
  },
  "author": "",
  "license": "ISC",
  "devDependencies": {  //开发打包用，这里不包含ES6转换ES5
    "css-loader": "^2.0.2",
    "file-loader": "^3.0.1",
    "less": "^3.9.0",
    "less-loader": "^4.1.0",
    "style-loader": "^0.23.1",
    "url-loader": "^1.1.2",
    "vue-loader": "^13.0.0",
    "vue-template-compiler": "^2.5.21",
    "webpack": "^3.6.0"
  },
  "dependencies": {  //
    "vue": "^2.5.21"
  }
}

```

我们一共在当前目录下执行

```npm
webpack
npm install webpack@3.6.0

css-loader
npm install css-loader@2.0.2 --save-dev

style-loader
npm install style-loader@0.23.1 --save-dev

less-loader
npm install --save-dev less-loader@4.1.0 less@3.9.0

url-loader
npm install --save-dev url-loader@1.1.2

es6转换成es5  //没有安装
npm install --save-dev babel-loader@7.1.5 babel-core@6.26.3 babel-preset-es2015@6.24.1

Vue
npm install vue@2.5.21 --save

file-loader 
npm install --save-dev file-loader@3.0.1

 Vue    //Vue的编译器，vue-template-compiler版本要和Vue版本匹配
npm install --save-dev vue-loader vue-template-compiler
```

## 17.4、el和template的区别

正常运行之后，我们来考虑另外一个问题:

- 如果我们希望将data中的数据显示在界面中，就必须是修改index.html

- 如果我们后面自定义了组件，也必须修改index.html来使用组件

- 但是html模板在之后的开发中，我并不希望手动的来频繁修改，是否可以做至
  呢?

定义template属性:

- 在前面的Vue实例中，我们定义了el属性，用于和index.html中的#app进行绑定，让Vue实例之后可以管理它其中的内容这里，我们可以将div元素中的([message}}内容删掉，只保留一个基本的id为div的元素
- 但是如果我依然希望在其中显示{message}}的内容，应该怎么处理呢?
- 我们可以再定义一个template属性，代码如下:

```js
import Vue from 'vue'
new Vue({
  el:'#app',
  template:`
  <div>
  <h2>{{message}}</h2>
  </div>`,
  data:{
    message: 'hello ceit'
  }
```

一旦我们定义，当时会帮我替换掉index.html里面我们#app，即template替换el

当我们的组件内容过多时候，我们的Vue实例会非常畸形，于是我们用前面的内容思想

```js
const App = {  //抽离
  template:`
  <div>
  <h2>{{message}}</h2>
  </div>`,
  data(){
    return{
    message: 'hello ceit'
  }}
}
new Vue({
  el:'#app',
  template: '<App/>', //替换
  components:{
    App
  }
})
```

我们为了简化main,js，创建一个新的文件夹Vue，在里面创建app.js

```js
export default
 {  //抽离
  template:`
  <div>
  <h2>{{message}}</h2>
  </div>`,
  data(){
    return{
    message: 'hello ceit'
  }}
}
```

然后再引入

```js

import Vue from 'vue'
import App from "./Vue/app";
new Vue({
  el:'#app',
  template: '<App/>', //替换
  components:{
    App
  }
})
```

我们最终为了最简洁，我们决定创建`App.vue`

```vue
<template>
  <div>
    <h2 class="title">{{message}}</h2>
  </div>
</template>

<script>
export default {
  name: "App",
  data(){
    return{
      message: 'hello ceit'
    }}
}
</script>

<style scoped>
 .title{
   color: aqua;
 }
</style>
```

## 17.5、plugin插件是什么

plugin是插件的意思，通常是用于对某个现有的架构进行扩展。

- webpack中的插件，就是对webpack现有功能的各种扩展，比如打包优化，文件压缩等等。

loader和plugin区别

- loader主要用于转换某些类型的模块，它是一个转换器。
- plugin是插件，它是对webpack本身的扩展，是一个扩展器。plugin的使用过程︰
  - 步骤一︰通过npm安装需要使用的plugins(某些webpack已经内置的插件不需要安装)
  - 步骤二: 在webpack.config.js中的plugins中配置插件。

## 17.6、BannerPlugin

我们先来使用一个最简单的插件，为打包的文件添加版权声明口该插件名字叫BannerPlugin，属于webpack自带的插件。

在webpack.config.js下

```js
const webpack = require('webpack')

module.exports = {
.....
  plugins:[
    new webpack.BannerPlugin('最终版权归ceit所有')
  ]
}
```

## 17.7、HtmlWebpackPlugin

目前，我们的index.html文件是存放在项目的根目录下的。

我们知道，在真实发布项目时，发布的是dist文件夹中的内容，但是dist文件夹中如果没有index.html文件，那么打包的js等文件也就没有意义了。

所以，我们需要将index.html文件打包到dist文件夹中，这个时候就可以使用HtmlWebpackPlugin插件HtmlWebpackPlugin插件可以为我们做这些事情:

自动生成一个index.html文件(可以指定模板来生成)口将打包的js文件，自动通过script标签插入到body中安装HtmlWebpackPlugin插件

```npm
npm install html-webpack-plugin --save-dev
```

```js
const HtmlwebpackPlugin =require('html-webpack-plugin')

module.exports = {
.....
  plugins:[
        new HtmlwebpackPlugin({
      template:'index.html'
    })
  ]
}
```

## 17.8、uglifyjs-webpack-plugin

**注意我们在发布时使用**

在项目发布之前，我们必然需要对js等文件进行压缩处理口这里，我们就对打包的js文件进行压缩

我们使用一个第三方的插件uglifyjs-webpack-plugin，并且版本号指定1.1.1，和CLI2保持一致

```npm
npm install uglifyjs-webpack-plugin@1.1.1 --save-dev
```

```js
const UglifyjsWebpackPluign = require('uglifyjs-webpack-plugin')

module.exports = {
.....
  plugins:[
       new UglifyjsWebpackPluign()
  ]
}
```

## 17.9、插件小结

webpack.config.js

```js
const path = require('path')
const webpack = require('webpack')
const HtmlwebpackPlugin = require('html-webpack-plugin')
const UglifyjsWebpackPluign = require('uglifyjs-webpack-plugin')


module.exports = {
  entry: './src/main.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
    publicPath:'dist/'
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      },
      {
        test: /\.less$/,
        use: [{
          loader: "style-loader" // creates style nodes from JS strings
        }, {
          loader: "css-loader" // translates CSS into CommonJS
        }, {
          loader: "less-loader" // compiles Less to CSS
        }
        ]
      },
      {
        test: /\.(png|jpg|gif)$/,
        use: [
          {
            loader: 'file-loader',
            options: {
              name: 'img/[name].[hash:8].[ext]'
            },

          }
        ]
      },
      {
        test: /\.vue$/,
        use:['vue-loader']
      }]
  },
  resolve:{
    alias:{
      'vue$':'vue/dist/vue.esm.js'
    }
  },
  plugins:[
    new webpack.BannerPlugin('最终版权归ceit所有'),
    new HtmlwebpackPlugin({
      template:'index.html'
    }),
    new UglifyjsWebpackPluign()
  ]
}
```

## 17.10、扩展：搭建本地服务器

**注意我们是开发时候需要**

webpack提供了一个可选的本地开发服务器，这个本地服务器基于node,js搭建，把我们的结果映射到内存里面，因为我们的内存读取速度比磁盘快很多很多

内部使用express框架，可以实现我们想要的让浏览器自动刷新显示我们修改后的结果。

不过它是一个单独的模块，在webpack中使用之前需要先安装它

```npm
npm install --save-dev webpack-dev-server@2.9.1
```

devserver也是作为webpack中的一个选项，选项本身可以设置如下属性

- contentBase :为哪一个文件夹提供本地服务，默认是根文件夹，我们这里要填写./distport:端口号
- inline :页面实时刷新
- historyApiFallback :在SPA页面中，依赖HTML5的history模式

配置服务的是哪个文件夹

```js
const UglifyjsWebpackPluign = require('uglifyjs-webpack-plugin')

module.exports = {
.....
  devServer:{
    contentBase: './dist',
    inline:true
  }
}
```

```js
{
  "name": "meetwebpack",
  "version": "1.0.0",
  "description": "",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build": "webpack",
    "dev": "webpack-dev-server  --open“ //添加映射
  },
  "author": "",
  "license": "ISC",
  "devDependencies": {
    "css-loader": "^2.0.2",
    "file-loader": "^3.0.1",
    "html-webpack-plugin": "^2.30.1",
    "less": "^3.9.0",
    "less-loader": "^4.1.0",
    "style-loader": "^0.23.1",
    "uglifyjs-webpack-plugin": "^1.1.1",
    "url-loader": "^1.1.2",
    "vue-loader": "^13.0.0",
    "vue-template-compiler": "^2.5.21",
    "webpack": "^3.6.0",
    "webpack-dev-server": "^2.9.3"
  },
  "dependencies": {
    "vue": "^2.5.21"
  }
}
```

## 17.11、配置文件分离

为了便于我们开发和发布两个模块的正确运行，我们创建文件夹如下

![image-20211017195150481](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211017195150481.png)

- 公共的配置放在`base.config.js`
- 开发的配置放在`dev.config.js`
- 生成的配置放在`prod.config.js`

因从我们改造我们的整个配置结构如下，安装组合器

```npm
npm install webpack-merge --save-dev
```

公共的配置放在`base.config.js`

```js 
const path = require('path')
const webpack = require('webpack')
const HtmlwebpackPlugin = require('html-webpack-plugin')



module.exports = {
  entry: './src/main.js',
  output: {
    path: path.resolve(__dirname, '../dist'),
    filename: 'bundle.js',
    publicPath:'dist/'
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      },
      {
        test: /\.less$/,
        use: [{
          loader: "style-loader" // creates style nodes from JS strings
        }, {
          loader: "css-loader" // translates CSS into CommonJS
        }, {
          loader: "less-loader" // compiles Less to CSS
        }
        ]
      },
      {
        test: /\.(png|jpg|gif)$/,
        use: [
          {
            loader: 'file-loader',
            options: {
              name: 'img/[name].[hash:8].[ext]'
            },

          }
        ]
      },
      {
        test: /\.vue$/,
        use:['vue-loader']
      }]
  },
  resolve:{
    alias:{
      'vue$':'vue/dist/vue.esm.js'
    }
  },
  plugins:[
    new webpack.BannerPlugin('最终版权归ceit所有'),
    new HtmlwebpackPlugin({
      template:'index.html'
    }),
  ]
}
```

开发的配置放在`dev.config.js`

```js
const webpackMerge =require('webpack-merge')
const baseConfig =require('./base.config')


module.exports = webpackMerge.merge(baseConfig,{
  devServer:{
    contentBase: './dist',
    inline:true}
})

```

生成的配置放在`prod.config.js`

```js
const UglifyjsWebpackPluign = require('uglifyjs-webpack-plugin')
const webpackMerge =require('webpack-merge')
const baseConfig =require('./base.config')

module.exports = webpackMerge.merge(baseConfig,{
  plugins:[
    new UglifyjsWebpackPluign()
  ]
})
```

最后配置webpack映射

```json
{
  "name": "meetwebpack",
  "version": "1.0.0",
  "description": "",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build": "webpack --config ./build/prod.config.js",
    "dev": "webpack-dev-server --open --config ./build/dev.config.js"
  },
  "author": "",
  "license": "ISC",
  "devDependencies": {
    "css-loader": "^2.0.2",
    "file-loader": "^3.0.1",
    "html-webpack-plugin": "^2.30.1",
    "less": "^3.9.0",
    "less-loader": "^4.1.0",
    "style-loader": "^0.23.1",
    "uglifyjs-webpack-plugin": "^1.1.1",
    "url-loader": "^1.1.2",
    "vue-loader": "^13.0.0",
    "vue-template-compiler": "^2.5.21",
    "webpack": "^3.6.0",
    "webpack-dev-server": "^2.9.3",
    "webpack-merge": "^5.8.0"
  },
  "dependencies": {
    "vue": "^2.5.21"
  }
}

```

# 18、Vuecli脚手架

如果你只是简单写几个Vue的Demo程序,那么你不需要Vue CLI.如果你在开发大型项目，那么你需要,并且必然需要使用Vue CLI

## 18.1、脚手架的介绍和安装


使用Vue.js开发大型应用时，我们需要考虑代码目录结构、项目结构和部署、热加载、代码单元测试等事情。

- 如果每个项目都要手动完成这些工作，那无疑效率比较低效，所以通常我们会使用一些脚手架工具来帮助完成这些事情。

CLI是什么意思?

- CLI是Command-Line Interface,翻译为命令行界面,但是俗称脚手架.Vue CLI是一个官方发布vue.js项目脚手架

- 使用vue-cli可以快速搭建Vue开发环境以及对应的webpack配置.

我们要装好**node.js和webpack**

```npm
//脚手架
npm install -g @vue/cli  
//脚手架2模板
npm install @vue/cli-init -g
```



## 18.2、初始化项目过程

在需要建立的文件夹下面

```npm
vue init webpack vueli2test   //脚手架2创建项目
```

![image-20211017223129766](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211017223129766.png)

## 18.3、目录结构解析

我们的原生js只能在浏览器中使用，为了能在服务器开发中实现，我们的js文件，有工程师在V8虚拟引擎上用C++制作了了node.js的

**js原来通过字节码才能被浏览器解析，但V8后直接被转换成二进制代码**，所有当我们的电脑有node就可以直接执行我们的js代码

比如我们有xxx.js

```js
console.log("aaa")
```

我们在终端课直接得到`aaa`

```npm
node XXX.js
```

**主要看我们的`package.json`文件，例如：**

我们首先看我们的**build.js**

```js
'use strict'
require('./check-versions')()

process.env.NODE_ENV = 'production'

const ora = require('ora')
const rm = require('rimraf')
const path = require('path')
const chalk = require('chalk')
const webpack = require('webpack')
const config = require('../config')
const webpackConfig = require('./webpack.prod.conf')  //对应文件下面的js

const spinner = ora('building for production...')
spinner.start()

rm(path.join(config.build.assetsRoot, config.build.assetsSubDirectory), err => {   //这是表示我们要是执行build时候把之前dist文件夹清空
  if (err) throw err
  webpack(webpackConfig, (err, stats) => {  //拿到webpack配置，执行相关配置并打包
    spinner.stop()
    if (err) throw err
    process.stdout.write(stats.toString({
      colors: true,
      modules: false,
      children: false, // If you are using ts-loader, setting this to true will make TypeScript errors show up during build.
      chunks: false,
      chunkModules: false
    }) + '\n\n')

    if (stats.hasErrors()) {
      console.log(chalk.red('  Build failed with errors.\n'))
      process.exit(1)
    }

    console.log(chalk.cyan('  Build complete.\n'))
    console.log(chalk.yellow(
      '  Tip: built files are meant to be served over an HTTP server.\n' +
      '  Opening index.html over file:// won\'t work.\n'
    ))
  })
})

```

`webpack.prod.conf,js`文件

```js
'use strict'
const path = require('path')
const utils = require('./utils')
const webpack = require('webpack')
const config = require('../config')
const merge = require('webpack-merge')
const baseWebpackConfig = require('./webpack.base.conf')  //合并工具
const CopyWebpackPlugin = require('copy-webpack-plugin')
const HtmlWebpackPlugin = require('html-webpack-plugin')
const ExtractTextPlugin = require('extract-text-webpack-plugin')
const OptimizeCSSPlugin = require('optimize-css-assets-webpack-plugin')
const UglifyJsPlugin = require('uglifyjs-webpack-plugin')

const env = require('../config/prod.env')

const webpackConfig = merge(baseWebpackConfig, {  //之前的结构一致
  module: {
    rules: utils.styleLoaders({
      sourceMap: config.build.productionSourceMap,
      extract: true,
      usePostCSS: true
    })
      ......
  }}）
 
```

**另外一个脚本的配置也可以按照以上的方式进行查看，这里不做多解释**

**第一个是build文件是基础设置，第二个config文件是设置变量值**

![image-20211017225930802](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211017225930802.png)

**`package-lock.json`里面是具体版本号，是真实安装的版本**

`README.md`就是开源项目下的建议读取文档

## 18.4、`runtimecomplier`和`runtimeonly`

我们可以清楚地看到我们的两个文件夹的区别在他们的main.js文件中

1. runtimecompiler

```js
// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App'

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  components: { App },
  template: '<App/>'
})

```

> 基本执行流程

2. runtimeonly

```js 
import Vue from 'vue'
import App from './App'

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  render: h => h(App)
})
```

其中我们介绍一下我们的箭头函数，这里的箭头函数是

```js
render:function(h){  //h是createElemnt,createElement('标签'，{标签的属性}，[''])或者createElement(template )
    return h(App)
}
```

> render到vdom到UI，所以我们的这个模式下代码更少，这里的template被vue-template-compiler处理了

![image-20211018102525078](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211018102525078.png)

基本执行流程:

1. 我们以后的html代码都会写成template
2. 解析成ast
3. **编译成render函数**
4. 转换成虚拟dom

## 18.5、Vuecli 3

vue-cli 3是基于webpack 4打造，vue-cli 2还是webapck 3

vue-cli 3的设计原则是**“0配置”**，移除的配置文件根目录下的，build和config等目录

vue-cli 3提供了vue ui命令，提供了可视化配置，更加人性化

移除了static文件夹，新增了public文件夹，并且index.html移动到public中

```npm
npm create my-project  //脚手架3创建项目
```

![image-20211018105805138](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211018105805138.png)

文件目录

```npm
>node_modules  //node包
>public        //相当于以前的Static
>src 			//我们以后要写的文件
.browserslistrc  //浏览器相关配置
.gitignore		//忽略文件
babel.config.js   //Babel是一个JS编译器，主要作用是将ECMAScript 2015+ 版本的代码，转换为向后兼容的JS语法，以便能够运行在当前和旧版本的浏览器或其他环境
package.json
package-lock.json
```

**其他配置是@vue下lib的webpack包下的Service找到**

## 18.6、启动本地服务器

```npm
vue ui
```

可以图形化地看我们的配置

![image-20211018145425691](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211018145425691.png)

**如果我们想改配置`vue.config.js`来配置，通过`module.exports`导出配置**

# 箭头函数

**一个函数作为另一个函数的参数的时候使用箭头函数。**

## 箭头函数的定义

1. 定义函数的方式

```js
const aaa = function(){
}
```

2. 对象字面量中定义函数

```js
const obj = {
    bbb(){
        
    }
}
```

3. **箭头函数**

``` js
const ccc = (参数列表)=>{}  //多个参数
const aaa = 参数=>{}  //一个参数
const aaa = ()=>{}  //没参数
const qqq = (参数)=> `一行代码` //只有一行代码
```

不管有没有返回值都可以这样写

## 19.2、箭头函数中this的使用

箭头函数中的this是如何查找的了?

箭头函数体内的`this`对象，就是定义**该函数时所在的作用域指向的对象**，而不是使用时所在的作用域指向的对象。

假如我们没有this就会向外寻找一层作用域{}里面有没有this，当一个函数在对象里面定义this代表当前对象

# Promise

## Promise的定义

`Promise`是**ES6异步编程的一种解决方案**，用于在进行网络请求会来处理异步事件。

使用封装一个网络请求的函数时，请求需要时间，不能马上得到结果。往往会传入另一个函数，在网络请求的数据请求成功时，通过传入的函数的形式将数据回调。

当网络请求非常复杂时，就会出现回调地狱。

```js
$ajax('url1',function (data1) {
  $ajax('data1['url2']',function (data2){
    $ajax('data2['url3']',function (data3){
      $ajax('data3['url4']',function (data4){
        $ajax('data4['url5']',function (data5){
        })
      })
    })
  })
})
```

程序可以正常运行，但代码复杂且难以维护。而`Promise`很好的解决了这一问题。

这里用一个定时器来模拟异步事件：

**定义`data`是从网络请求的数据，定义`console.log`是数据处理方式。**

```js
setTimeout( function (){
let data = 'Hello World'
console.log ( content);}，1000)
```

转化为`Promise`函数：

```js
new Promise( (resolve, reject) =>{
    setTimeout( function () {
		resolve( 'Hello World ' )
        reject( 'Error Data ' )}， 1000)
}).then(data => {
    console.log(data) ;
 }).catch(error => {
    console.log(error);})
```

## Promise的使用

有异步操作的时候需要对即将进行的异步操作进行封装。

`new Promise()`时保存状态信息，并传入函数参数`resolve`**解决**和`reject`**拒绝**。当网络请求会传回一些`data`，假如在`data`下面有还没处理的时而且不想`data`在这里处理，使用`resolve`把数据传入到下面的的`then`里，在`then`里面处理。

```js
new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve()
    }, 1000).then(() => {
      console.log('helloceit');
      console.log('helloceit');
      console.log('helloceit');
      console.log('helloceit');
      console.log('helloceit');

      return new Promise((resolve, reject) => {
        setTimeout(() => {
          resolve()
        }, 1000).then(() => {
          console.log('byeceit');
          console.log('byeceit');
          console.log('byeceit');
          console.log('byeceit');
          console.log('byeceit');
          console.log('byeceit');

          return new Promise((resolve, reject) => {
            setTimeout(() => {
              console.log('byeVue');
              console.log('byeVue');
            }, 1000)
          })
        })
      })
    })
  })
```

## Promise的状态

在开发中有异步操作时需要包装一个`Promise`。

异步操作会有**三种状态**：

1、`pending`等待状态。比如正在进行网络请求，或者定时器没有到时间。

2、`fulfill`满足状态。主动回调`resolve`时处于该状态，且会回调`.then（）`。

3、`reject` 拒绝状态。主动回调`reject`时处于该状态，且会回调`.catch（）`。

```js
.then(data =>{
    //处理数据
},err =>{
    //报错操作
})
```

## 21.4、处理数据的链式调用

- 我们的在第一次接受数据以后对数据进行处理
- 我们处理完以后在进行下一个处理，对应也要对应的数据处理
- ......

怎么完成这样的处理呢？

```js
  //参数本身是一个函数，两个参数resolve和reject，一个解决，一个拒绝
  //resolve和reject本身也是函数,then里面的参数也是参数
  new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve('aaa')
    }, 1000)
  }).then(res => {
    console.log('helloceit');

    return new Promise(resolve => {
      resolve(res + '111')
    }).then(() => {
      console.log('byeceit');
      return new Promise(resolve => {
        resolve(res + '222')
      }).catch(res => {
        console.log(res);
      })
    })
  })
```

**在Resolve里面对数据进行处理即可，为了简洁**

```js
  //参数本身是一个函数，两个参数resolve和reject，一个解决，一个拒绝
  //resolve和reject本身也是函数,then里面的参数也是参数
  new Promise(resolve => {
    setTimeout(() => {
      resolve('aaa')
    }, 1000)
  }).then(res => {
    console.log('helloceit');
    return Promise.resolve(res + '111')
  }).then(res => {
    console.log('byeceit');
    return Promise.resolve(res + '222')
  }).then(res => {
    console.log(res);
  })
```

**为了更加简洁，省略Promise.resolve，它内部会帮我包装**

```js
  //参数本身是一个函数，两个参数resolve和reject，一个解决，一个拒绝
  //resolve和reject本身也是函数,then里面的参数也是参数
  new Promise(resolve => {
    setTimeout(() => {
      resolve('aaa')
    }, 1000)
  }).then(res => {
    console.log('helloceit');
    return res + '111'
  }).then(res => {
    console.log('byeceit');
    return res + '222'
  }).then(res => {
    console.log(res);
  })
```

**假如主动一个错误的，我们就得 return Promise.reject了，也可以手动throw手动抛出异常，最后在catch捕获异常**

## 21.5、promise的all方法

我们的一个需求需要两个请求都请求到才能完成我们的目标

**我们可以用我们的promise包装两个异步请求，然后在最后一起回调**

```js
  Promise.all([
    new Promise(resolve => {
      $.ajax({
        url:'url1',
        success: function (data) {
          resolve(data)
        }
      })
    }),
    new Promise(resolve => {
      $.ajax({
        url:'urlr2',
        success: function (data) {
          resolve(data)
        }
      })
    }) ]).then(results =>{
    console.log(results);
  })
```

resolve里面也可以传对象

```js
resolve({name:'key',age:18})
```

# 22、Vue的深入响应式原理

**Vue 最独特的特性之一，是其非侵入性的响应式系统**。数据模型仅仅是普通的 JavaScript 对象。而当你修改它们时，视图会进行更新。

当你把一个普通的 JavaScript 对象传入 Vue 实例作为 `data` 选项，Vue 将遍历此对象所有的 property，并使用 [`Object.defineProperty`](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Object/defineProperty) 把这些 property 全部转为 [getter/setter](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide/Working_with_Objects#定义_getters_与_setters)。`Object.defineProperty` 是 ES5 中一个无法 shim 的特性

> 注意，是这里Vue实例中的

这些 getter/setter 对用户来说是不可见的，但是在内部它们让 Vue 能够追踪依赖，在 property 被访问和修改时通知变更。这里需要注意的是不同浏览器在控制台打印数据对象时对 getter/setter 的格式化并不同，所以建议安装 [vue-devtools](https://github.com/vuejs/vue-devtools) 来获取对检查数据更加友好的用户界面。

每个组件实例都对应一个 **watcher** 实例，它会在组件渲染的过程中把“接触”过的数据 property 记录为依赖。之后当依赖项的 setter 触发时，会通知 watcher，从而使它关联的组件重新渲染。

![image-20211022090907181](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211022090907181.png)

由于 JavaScript 的限制，Vue **不能检测**数组和对象的变化。尽管如此我们还是有一些办法来回避这些限制并保证它们的响应性。

> 对应普通的数组和对象，我们需要另外一种方法去进行响应式编程

## 22.1、声明响应式 property

由于 Vue 不允许动态添加根级响应式 property，所以你必须在初始化实例前声明所有根级响应式 property，哪怕只是一个空值：

```
var vm = new Vue({
  data: {
    // 声明 message 为一个空值字符串
    message: ''
  },
  template: '<div>{{ message }}</div>'
})
// 之后设置 `message`
vm.message = 'Hello!'
```

如果你未在 `data` 选项中声明 `message`，Vue 将警告你渲染函数正在试图访问不存在的 property。

这样的限制在背后是有其技术原因的，它消除了在依赖项跟踪系统中的一类边界情况，也使 Vue 实例能更好地配合类型检查系统工作。

但与此同时在代码可维护性方面也有一点重要的考虑：`data` 对象就像组件状态的结构 (schema)。提前声明所有的响应式 property，可以让组件代码在未来修改或给其他开发人员阅读时更易于理解。

**因从我们必须有对应的对象和数值才能进行属性的声明响应式**

## 22.2、检测变化的注意事项

### 22.2、对于对象

Vue 无法检测 property 的添加或移除。由于 Vue 会在初始化实例时对 property 执行 getter/setter 转化，所以 property 必须在 `data` 对象上存在才能让 Vue 将它转换为响应式的。例如：

```js
var vm = new Vue({
  data:{
    a:1
  }
})

// `vm.a` 是响应式的

vm.b = 2
// `vm.b` 是非响应式的
```

> 只有每次初始实例化的时候才会触发property 执行 getter/setter 转化

#### `Vue.set`在对象插入数值

对于已经创建的实例，Vue 不允许动态添加根级别的响应式 property。但是，可以使用 `Vue.set(object, propertyName, value)` 方法向嵌套对象添加响应式 property。**注意我们这里要导入Vue**。例如，对于：

```js
Vue.set(vm.someObject, 'b', 2)
```

> 第一个参数someObject是data中的一个对象，后面是kv值，其中我们的vm.someObject也可以写成this.someObject

**在stu里面添加元素：**

```vue
<template>
  <div id="app">
    <h2>{{stu}}</h2>
    <button @click="addadvise">!!</button>
  </div>
</template>

<script>
import Vue from 'vue'
export default {
  name: 'App',
  data:function(){
      return{
        stu:{
          name:'ceit',
        }
      }
    }
  ,
  methods:{
    addadvise(){
      Vue.set(this.stu, 'b', 2)  //这里是Vue
    }
  }
}
</script>
<style>

</style>

```

#### `vm.$set`在对象插入数值

您还可以使用 `vm.$set` 实例方法，这也是全局 `Vue.set` 方法的别名：

```js
this.$set(this.someObject,'b',2)
```

**在stu里面添加元素：**

```Vue
<template>
  <div id="app">
    <h2>{{stu}}</h2>
    <button @click="addadvise">!!</button>
  </div>
</template>

<script>
export default {
  name: 'App',
  data:function(){
      return{
        stu:{
          name:'ceit',
        }
      }
    }
  ,
  methods:{
    addadvise(){
      this.$set(this.stu, 'b', 2)  //这里是this
    }
  }
}
</script>
<style>
</style>

```

有时你可能需要为已有对象赋值多个新 property，比如使用 `Object.assign()` 或 `_.extend()`。但是，这样添加到对象上的新 property 不会触发更新。在这种情况下，你应该用原对象与要混合进去的对象的 property 一起创建一个新的对象。

```js
// 代替 `Object.assign(this.someObject, { a: 1, b: 2 })`
this.someObject = Object.assign({}, this.someObject, { a: 1, b: 2 })
```

**在stu里面添加元素：**

```vue
<template>
  <div id="app">
    <h2>{{stu}}</h2>
    <button @click="addadvise">!!</button>
  </div>
</template>

<script>
import Vue from 'vue'
export default {
  name: 'App',
  data:function(){
      return{
        stu:{
          name:'ceit',
        }
      }
    }
  methods:{
    addadvise(){
      this.stu = Object.assign({}, this.stu, { a: 1, b: 2 })
    }
  }
}
</script>
<style>
</style>
```

**扩展1：添加Vue里面数组里面的对象改怎么修改**

在本质上我们修改的还是对象的值，所以我们只要在第一个传进来的参数的数组加上对应的下标即可

**扩展2：添加Vue里面的对象改怎么删除**

把对应的set改成delete

### 22.3、对于数组

Vue 不能检测以下数组的变动：

1. 当你利用索引直接设置一个数组项时，例如：`vm.items[indexOfItem] = newValue`
2. 当你修改数组的长度时，例如：`vm.items.length = newLength`

举个例子：

```js
var vm = new Vue({
  data: {
    items: ['a', 'b', 'c']
  }
})
vm.items[1] = 'x' // 不是响应性的
vm.items.length = 2 // 不是响应性的
```

为了解决第一类问题，以下两种方式都可以实现和 `vm.items[indexOfItem] = newValue` 相同的效果，同时也将在响应式系统内触发状态更新：

```js
// Vue.set
Vue.set(vm.items, indexOfItem, newValue)
// Array.prototype.splice
vm.items.splice(indexOfItem, 1, newValue)
```

你也可以使用 [`vm.$set`](https://cn.vuejs.org/v2/api/#vm-set) 实例方法，该方法是全局方法 `Vue.set` 的一个别名：

```js
vm.$set(vm.items, indexOfItem, newValue)
```

为了解决第二类问题，你可以使用 `splice`：

```js
vm.items.splice(newLength)
```

> 因为我们的Vue两个方法在22.1中已经进行实例分析，所以我们在这里不再进行实例分析，入上图即可

## 22.4、异步更新队列（了解）

可能你还没有注意到，Vue 在更新 DOM 时是**异步**执行的。只要侦听到数据变化，Vue 将开启一个队列，并缓冲在同一事件循环中发生的所有数据变更。如果同一个 watcher 被多次触发，只会被推入到队列中一次。这种在缓冲时去除重复数据对于避免不必要的计算和 DOM 操作是非常重要的。然后，在下一个的事件循环“tick”中，Vue 刷新队列并执行实际 (已去重的) 工作。Vue 在内部对异步队列尝试使用原生的 `Promise.then`、`MutationObserver` 和 `setImmediate`，如果执行环境不支持，则会采用 `setTimeout(fn, 0)` 代替。

例如，当你设置 `vm.someData = 'new value'`，该组件不会立即重新渲染。当刷新队列时，组件会在下一个事件循环“tick”中更新。多数情况我们不需要关心这个过程，但是如果你想基于更新后的 DOM 状态来做点什么，这就可能会有些棘手。虽然 Vue.js 通常鼓励开发人员使用“数据驱动”的方式思考，避免直接接触 DOM，但是有时我们必须要这么做。为了在数据变化之后等待 Vue 完成更新 DOM，可以在数据变化之后立即使用 `Vue.nextTick(callback)`。这样回调函数将在 DOM 更新完成后被调用。例如：

```
<div id="example">{{message}}</div>
var vm = new Vue({
  el: '#example',
  data: {
    message: '123'
  }
})
vm.message = 'new message' // 更改数据
vm.$el.textContent === 'new message' // false
Vue.nextTick(function () {
  vm.$el.textContent === 'new message' // true
})
```

在组件内使用 `vm.$nextTick()` 实例方法特别方便，因为它不需要全局 `Vue`，并且回调函数中的 `this` 将自动绑定到当前的 Vue 实例上：

```
Vue.component('example', {
  template: '<span>{{ message }}</span>',
  data: function () {
    return {
      message: '未更新'
    }
  },
  methods: {
    updateMessage: function () {
      this.message = '已更新'
      console.log(this.$el.textContent) // => '未更新'
      this.$nextTick(function () {
        console.log(this.$el.textContent) // => '已更新'
      })
    }
  }
})
```

因为 `$nextTick()` 返回一个 `Promise` 对象，所以你可以使用新的 [ES2017 async/await](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Statements/async_function) 语法完成相同的事情：

```js
methods: {
  updateMessage: async function () {
    this.message = '已更新'
    console.log(this.$el.textContent) // => '未更新'
    await this.$nextTick()
    console.log(this.$el.textContent) // => '已更新'
  }
}
```

## 23.9、ES6新语法：对象的解构

```js
const obj={
    name:"",
    age:18,
    height:1.88
    address:'???'
}
const{name,height,age}=obj //按名字对应赋值
```

即假如有一个函数的参数是一个对象，而我们只想要对应的几个值，我们就可以拿这种写法

## 23.10、ES6的新语法：数组的解析

```js
const names = ['name','kobe','james']
const[name1,name2,name3] = names;
```

# 网络请求的封装

`Vue`在进行发送网络请求时，一般选择`axios`，它优点显著，使用方便。在这对网络请求进行介绍。

## Jsonp

### Jsonp的定义

由于浏览器同源策略限制，网页无法通过`Ajax`请求非同源的接口数据。而`JSONP`是`JSON`的一种”使用模式“，可用于解决主流浏览器的跨域数据访问的问题。

在前端开发中，最常见的网络请求方式就是`JSONP`。

### Jsonp的原理

项目部署在`Dome1.com`服务器上时，是不能直接访问`Dome2.com`服务器上的资料的。`JSONP`的核心在于通过`<script>`标签的`src`来帮助我们请求数据，将数据当做一个`javascript`的函数来执行，并且执行的过程中传入我们需要的`json`。

## axios

`Axios` 是一个基于 `promise` 网络请求库，作用于`node.js`和浏览器中。

其支持多种请求方式：

```js
axios(config)
axios.request(config)
axios.get(url[, config])
axios.delete(url[, config])
axios.head(url[, config])
axios.post(url[,data[, config]l)
axios.put(url[, data[, config]l)
axios.patch(url[, data[, config]l)
```

### axios的安装

在对应项目的`terminal`上输入命令：

```npm
npm install axios --save
```

### axios的使用

```js
axios({
  url:'http://123.207.32.32:8000/home/multidata'
}).then(res => console.log(res))

axios({
  url:'http://123.207.32.32:8000/home/data',
  params:{                //专门针对get请求的参数拼接，这里是对象,对我们自动拼接
    type:'pop',
    page:1
  }
}).then(res => console.log(res))
```

## 24.3、axios发送并发请求

有时候,我们可能需求同时发送两个请求使用axios.all,可以放入多个请求的数组.

有时候，我们可能需求同时发送两个请求使用公理.ALL，可以放入多个请求的数组.

- axios.al(I)返回的结果是一个数组，使用axios.spread可将数组[res1,res2]展开为res1, res2

- 返回的结果是一个数组，使用公理[res1，res2]展开为Are 1，Res 2

```js
axios.all([axios({
    url:'http://123.207.32.32:8000/home/multidata'}),
 axios({
    url:'http://123.207.32.32:8000/home/data',
    params:{                //专门针对get请求的参数拼接，这里是对象,对我们自动拼接
      type:'pop',
      page:1  }
 })
          ]).then(axios.spread((res1,res2)  => {
    
}))
```

## 24.4、axios的全局配置

在上面的示例中,我们的BaseURL是固定的

- 事实上,在开发中可能很多参数都是固定的.

- 这个时候我们可以进行一些抽取，也可以利用axios的全局配置

  > axios.defaults.可以用来全局配置

  - axios.defaults.baseURL = ‘123.207.32.32:8000’
  - axios.defaults.headers.post[ ‘content-Type’] = ‘application/x -www-form-urlencoded’;
  - .....如：

![image-20211026182250793](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211026182250793.png)



**注意：**

**我们的方法是`GET`时候，我们的传参是`params`**

**我们的方法是`POST`时候，我们的传参是`data`**

## 24.5、axios的实例

为什么要创建axios的实例呢?

- 当我们从axios模块中导入对象时,使用的实例是默认的实例.

- 当给该实例设置一些默认配置时,这些配置就被固定下来了.

- 但是后续开发中,某些配置可能会不太一样.

- 比如某些请求需要使用特定的`baseURL`或者`timeout`或者`content-Type`等.

- 这个时候，我们就可以创建新的实例,并且传入属于该实例的配置信息.

> 如我们的首页的IP不一样，如果我们要是用默认一个default以后会导致全局的都变得一致。
>
> 在公司中，我们会把不同的资源放进不同服务器，并设立反向代理（nginx）来看哪个服务器访问量比较小，把数据转发
>
> 在上面的情况，只有一个axios的实例会不合适

```js
const instance1 = axios.create({
    baseURL:'http://222.111.33.33:8000',
    timeout:5000
})
instance1({
    url:'/'
}).then(res=> console.log(res))
```

## 24.6、axios的实例和模块封装

如果我们不对我们axios进行封装，我们的代码会如下图

![image-20211026190516264](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211026190516264.png)

**这样的话，如果框架A在某天宣布不在更新的时候，我们的的程序就得进行对应的替换，为了解决，我们选择封装（加一层）**

![image-20211026190337660](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211026190337660.png)

那如果我们替换框架的时候，我们的只需要修改文件即可，

**方式一：**

**1.我们创建新的文件夹network，并编写我们新的js**

```js
import axios from "axios";
export function request(config,success,failure) {  //success,failure是函数
  //1.创建Axios实例
  const instance = axios.create({
    baseURL:'http://123.207.32.32:8000',
    timeout:5000
  })

  instance(config)
    .then(res=>{
      // console.log(res);
      success(res)
    })
    .catch(err=>{
      // console.log(err);
      failure(err)
    })

}
```

**2.前端引入并调用这个函数**

```js
import {request} from 'network/request'
request({url: '/home'}, res => console.log(res), err => console.log(err))
```

**方式二：**

**1.我们创建新的文件夹network，并编写我们新的js**

```js
import axios from "axios";
export function request(config) {  //success,failure是函数
  //1.创建Axios实例
  const instance = axios.create({
    baseURL:'http://123.207.32.32:8000',
    timeout:5000
  })

  instance(config.baseConfig)
    .then(res=>{
      // console.log(res);
      config.success(res)
    })
    .catch(err=>{
      // console.log(err);
      config.failure(err)
    })

}
```

**2.前端引入并调用这个函数**

```js
import {request} from 'network/request'
request({baseConfig:{
    
},
success:function(res){
    
},
failure:function(err){
    
}
})
```

**方式三：（实际方法）**

**1.我们创建新的文件夹network，并编写我们新的js**

```js
import axios from "axios";
export function request(config) {  //success,failure是函数
  return new Promise((resolve,reject)=>{
    //1.创建Axios实例
  const instance = axios.create({
    baseURL:'http://123.207.32.32:8000',
    timeout:5000
  })

  instance(config)
    .then(res=>{
	resolve(res)
    })
    .catch(err=>{
	reject(err)
    })
})
}
```

**2.前端引入并调用这个函数**

```js
import {request} from 'network/request'
request({
    url:''
}).then(res=>console.log(res))
  .catch(err=>console.log(err))
```

**3.我们觉得没必要这样写了**

```js
import axios from "axios";
export function request(config) {  //success,failure是函数
    //1.创建Axios实例
  const instance = axios.create({
    baseURL:'http://123.207.32.32:8000',
    timeout:5000
  })

return instance(config)  //它本身就是一个promise
}
```

## 24.7、axios拦截器的使用

axios提供了拦截器，用于我们在发送每次请求或者得到相应后，进行对应的处理。如何使用拦截器呢?

```js
import axios from "axios";

export function request(config, success, failure) {  //success,failure是函数
  //1.创建Axios实例
  const instance = axios.create({
    baseURL: 'http://123.207.32.32:8000',
    timeout: 5000
  })
  instance.interceptors.request.use(config=>{
    console.log(config);
    // 1.比如config中的一些信息不符合服务器的要求

    // 2.比如每次发送网络请求时，都希望在界面中显示一个请求的图标

    // 3.某些网络请求（比如登录（token))，我们必须携带一些特殊信息

    return config //有拿有还，再借不难
  },error => {

  })
  instance.interceptors.response.use(res=>{  
    
    return res.data //res里面有很多东西，我们的数据只在data里面
  },error => {
    
  })
  return instance(config)  //instance(config)返回promise


}
```



