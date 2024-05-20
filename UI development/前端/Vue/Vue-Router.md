# Vue Router

## 发展历程

### **后端路由阶段**

早期的网站开发整个HTML页面是由服务器来渲染的.

- 服务器直接生产渲染好对应的HTML页面,返回给客户端进行展示.

但是,一个网站,这么多页面服务器如何处理呢?

- 一个页面有自己对应的网址,也就是URL.
- URL会发送到服务器,服务器会通过正则对该URL进行匹配,并且最后交给一个Controller进行处理.
- Controller进行各种处理,最终生成HTML或者数据,返回给前端.

- 这就完成了一个IO操作.

上面的这种操作,就是后端路由.

- 当我们页面中需要请求不同的路径内容时,交给服务器来进行处理,服务器渲染好整个页面,并且将页面返回给客户顿.
- 这种情况下渲染好的页面,不需要单独加载任何的js和css,可以直接交给浏览器展示,这样也有利于SEO的优化.

后端路由的缺点:

- 一种情况是整个页面的模块由后端人员来编写和维护的.
- 另一种情况是前端开发人员如果要开发页面,需要通过PHP和Java等语言来编写页面代码.
- 而且通常情况下HTML代码和数据以及对应的逻辑会混在一起,编写和维护都是非常糟糕的事情.

### **前后端分离阶段**

- 随着Ajax的出现,有了前后端分离的开发模式.
- 后端只提供API来返回数据,前端通过Ajax获取数据,并且可以通过JavaScript将数据渲染到页面中.
- 这样做最大的优点就是前后端责任的清晰,后端专注于数据上,前端专注于交互和可视化上.
- 并且当移动端(iOS/Android)出现后,后端不需要进行任何处理,依然使用之前的一套API即可.目前很多的网站依然采用这种模式开发.

![image-20211018162131621](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211018162131621.png)

我们把这个过程叫做**前端渲染**

### **单页面富应用阶段**

其实SPA最主要的特点就是在前后端分离的基础上加了一层前端路由，也就是前端来维护—套路由规则.

**即整个网站只有一个html页面**



![image-20211018170118190](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211018170118190.png)

前端路由的route只要在点击的情况下，触发了对应的URL，我们的前端就会去对应的js里面找到对应URL的资源进行抽取，**其中抽取的资源，就是我们的组件**，来渲染我们的页面。

## 起步

用 Vue + Vue Router 创建单页应用非常简单：通过 Vue.js，我们已经用组件组成了我们的应用。当加入 Vue Router 时，我们需要做的就是将我们的组件映射到路由上，让 Vue Router 知道在哪里渲染它们。下面是一个基本的例子：

### HTML

- **`<router-link>`**

请注意，我们没有使用常规的 `a` 标签，而是使用一个自定义组件 `router-link` 来创建链接。

**`<router-link>` :该标签是一个vue-router中已经内置的组件,它会被渲染成一个<a>标签.**

-  **tag**可以指定<router-link>之后渲染成什么组件,比如上面的代码会被渲染成一个<li>元素,而不是<a>
-  **replace**: replace不会留下history记录,所以指定replace的情况下,后退键返回不能返回到上一个页面中
-  **active-class**:当<router-link>对应的路由匹配成功时,会自动给当前元素设置一个router-link-active的class,设置active-class可以修改默认的名称.
   - 在进行高亮显示的导航菜单或者底部tabbar时,会使用到该类.
   - 但是通常不会修改类的属性,会直接使用默认的router-link-active即可.

- **`<router-view>`**

**`<router-view>`:该标签会根据当前的路径,动态渲染出不同的组件.**

`router-view` 将显示与 url 对应的组件。你可以把它放在任何地方，以适应你的布局。

```html
<script src="https://unpkg.com/vue/dist/vue.js"></script>
<script src="https://unpkg.com/vue-router/dist/vue-router.js"></script>

<div id="app">
  <h1>Hello App!</h1>
  <p>
    <router-link to="/foo">Go to Foo</router-link>
    <router-link to="/bar">Go to Bar</router-link>
  </p>
  <!-- 路由出口 -->
  <!-- 路由匹配到的组件将渲染在这里 -->
  <router-view></router-view>
</div>
```

### JavaScript

```js
// 1. 定义 (路由) 组件。
// 可以从其他文件 import 进来
const Foo = { template: '<div>foo</div>' }
const Bar = { template: '<div>bar</div>' }

// 2. 定义路由
// 每个路由应该映射一个组件。 其中"component" 可以是
// 通过 Vue.extend() 创建的组件构造器，
// 或者，只是一个组件配置对象。
// 我们晚点再讨论嵌套路由。
const routes = [
  { path: '/foo', component: Foo },
  { path: '/bar', component: Bar }
]

// 3. 创建 router 实例，然后传 `routes` 配置
// 你还可以传别的配置参数, 不过先这么简单着吧。
const router = new VueRouter({
  routes // (缩写) 相当于 routes: routes
})

// 4. 创建和挂载根实例。
// 记得要通过 router 配置参数注入路由，
// 从而让整个应用都有路由功能
const app = new Vue({
  router
}).$mount('#app')

// 现在，应用已经启动了！
```

通过注入路由器，我们可以在任何组件内通过 `this.$router` 访问路由器，也可以通过 `this.$route` 访问当前路由：

```js
// Home.vue
export default {
  computed: {
    username() {
      // 我们很快就会看到 `params` 是什么
      return this.$route.params.username
    }
  },
  methods: {
    goBack() {
      window.history.length > 1 ? this.$router.go(-1) : this.$router.push('/')
    }
  }
}
```

要在 `setup` 函数中访问路由，请调用 `useRouter` 或 `useRoute` 函数。我们将在 [Composition API](https://next.router.vuejs.org/zh/guide/advanced/composition-api.html#在-setup-中访问路由和当前路由) 中了解更多信息。

在整个文档中，我们会经常使用 `router` 实例，请记住，`this.$router` 与直接使用通过 `createRouter` 创建的 `router` 实例完全相同。我们使用`this.$router` 的原因是，我们不想在每个需要操作路由的组件中都导入路由。

## Route对象

### $route对象

**表示当前的路由信息，包含了当前 URL 解析得到的信息。包含当前的路径，参数，query对象等。**

 **1.**  **`$route.path`**   字符串，对应当前路由的路径，总是解析为绝对路径，如"/foo/bar"。

  **2.**  **`$route.params`**   一个 key/value 对象，包含了 动态片段 和 全匹配片段，   如果没有路由参数，就是一个空对象。

  **3.**  **`$route.query`**   一个 key/value 对象，表示 URL 查询参数。   例如，对于路径 /foo?user=1，则有$route.query.user == 1，   如果没有查询参数，则是个空对象。

  **4.**  **`$route.hash`**   当前路由的hash值 (不带#) ，如果没有 hash 值，则为空字符串。锚点*

  **5.**  **`$route.fullPath`**   完成解析后的 URL，包含查询参数和hash的完整路径。

  **6.**  **`$route.matched`**   数组，包含当前匹配的路径中所包含的所有片段所对应的配置参数对象。

  **7.**  **`$route.name`**  当前路径名字

  **8.**  **`$route.meta`** 路由元信息

### $router对象

**是全局路由的实例，是router构造方法的实例。**

**1.push**

- 字符串**`this.$router.push('home')`**

- 对象**`this.$router.push({path:'home'})`**

- 命名的路由**`this.$router.push({name:'user',params:{userId:123}})`**

- 带查询参数，变成 **`/register?plan=123  this.$router.push({path:'register',query:{plan:'123'}})`**

- push方法其实和<router-link :to="...">是等同的。

> 注意：push方法的跳转会向 history 栈添加一个新的记录，当我们点击浏览器的返回按钮时可以看到之前的页面。

**2.go**

   页面路由跳转 

   前进或者后退**`this.$router.go(-1)`** // 后退

**3.replace**

  push方法会向 history 栈添加一个新的记录，而replace方法是替换当前的页面，

  不会向 history 栈添加一个新的记录

**4.一般使用replace来做404页面**

  **`this.$router.replace('/')`**

  配置路由时path有时候会加 '/' 有时候不加,以'/'开头的会被当作根路径，就不会一直嵌套之前的路径。

$router对象是全局路由的实例，是router构造方法的实例。

## 动态路由匹配

我们经常需要把某种模式匹配到的所有路由，全都映射到同个组件。

例如，我们有一个 `User` 组件，**对于所有 ID 各不相同的用户，都要使用这个组件来渲染**。那么，我们可以在 `vue-router` 的路由路径中使用“动态路径参数”(dynamic segment) 来达到这个效果：

```js
const User = {
  template: '<div>User</div>'
}

const router = new VueRouter({
  routes: [
    // 动态路径参数 以冒号开头
    { path: '/user/:id', component: User }
  ]
})
```

现在像 `/users/johnny` 和 `/users/jolyne` 这样的 URL 都会映射到同一个路由。

*路径参数* 用冒号 `:` 表示。当一个路由被匹配时，它的 *params* 的值将在每个组件中以 `this.$route.params` 的形式暴露出来，**我们的params里面的key是path里面的:key**。因此，我们可以通过更新 `User` 的模板来呈现当前的用户 ID：

```js
const User = {
  template: '<div>User {{ $route.params.id }}</div>'
}
```

你可以在一个路由中设置多段“路径参数”，对应的值都会设置到 `$route.params` 中。例如：

| 模式                          | 匹配路径            | $route.params                          |
| ----------------------------- | ------------------- | -------------------------------------- |
| /user/:username               | /user/evan          | `{ username: 'evan' }`                 |
| /user/:username/post/:post_id | /user/evan/post/123 | `{ username: 'evan', post_id: '123' }` |

除了 `$route.params` 外，`$route` 对象还提供了其它有用的信息，例如，`$route.query` (如果 URL 中有查询参数)、`$route.hash` 等等。

### 响应路由参数的变化

提醒一下，当使用路由参数时，例如从 `/user/foo` 导航到 `/user/bar`，**原来的组件实例会被复用**。因为两个路由都渲染同个组件，比起销毁再创建，复用则显得更加高效。**不过，这也意味着组件的生命周期钩子不会再被调用**。

复用组件时，想对路由参数的变化作出响应的话，你可以简单地 watch (监测变化) `$route` 对象：

```js
const User = {
  template: '...',
  watch: {
    $route(to, from) {
      // 对路由变化作出响应...
    }
  }
}
```

或者使用 2.2 中引入的 `beforeRouteUpdate` [导航守卫](https://router.vuejs.org/zh/guide/advanced/navigation-guards.html)：

```js
const User = {
  template: '...',
  beforeRouteUpdate(to, from, next) {
    // react to route changes...
    // don't forget to call next()
  }
}
```

### 捕获所有路由或 404 Not found 路由

常规参数只匹配 url 片段之间的字符，用 `/` 分隔。如果我们想匹配**任意路径**，我们可以使用自定义的 *路径参数* 正则表达式，在 *路径参数* 后面的括号中加入 正则表达式 :

```js
const routes = [
  // 将匹配所有内容并将其放在 `$route.params.pathMatch` 下
  { path: '/:pathMatch(.*)*', name: 'NotFound', component: NotFound },
  // 将匹配以 `/user-` 开头的所有内容，并将其放在 `$route.params.afterUser` 下
  { path: '/user-:afterUser(.*)', component: UserGeneric },
]
```

在这个特定的场景中，我们在括号之间使用了自定义正则表达式，并将`pathMatch` 参数标记为可选可重复。

这样做是为了让我们在需要的时候，可以通过将 `path` 拆分成一个数组，直接导航到路由：

```
this.$router.push({
  name: 'NotFound',
  params: { pathMatch: this.$route.path.split('/') },
})
```

### 高级匹配模式

Vue Router 使用自己的路径匹配语法，其灵感来自于 `express`，因此它支持许多高级匹配模式，如可选的参数，零或多个 / 一个或多个，甚至自定义的正则匹配规则。

## 路由的匹配语法

大多数应用都会使用 `/about` 这样的静态路由和 `/users/:userId` 这样的动态路由，就像我们刚才在[动态路由匹配](https://next.router.vuejs.org/zh/guide/essentials/dynamic-matching.html)中看到的那样，但是 Vue Router 可以提供更多的方式！

> 为了简单起见，所有的路由**都省略了 `component` 属性**，只关注 `path` 值。

### 在参数中自定义正则

当定义像 `:userId` 这样的参数时，我们内部使用以下的正则 `([^/]+)` (至少有一个字符不是斜杠 `/` )来从 URL 中提取参数。

这很好用，除非你需要根据参数的内容来区分两个路由。想象一下，两个路由 `/:orderId` 和 `/:productName`，两者会匹配完全相同的 URL

```js
const routes = [
  { path: '/:orderId' },
  { path: '/:productName' },
]
```

所以我们需要一种方法来区分它们。最简单的方法就是在路径中添加一个静态部分来区分它们：

```js
const routes = [
  // 匹配 /o/3549
  { path: '/o/:orderId' },
  // 匹配 /p/books
  { path: '/p/:productName' },
]
```

但在某些情况下，我们并不想添加静态的 `/o` /`p` 部分。由于，`orderId` 总是一个数字，而 `productName` 可以是任何东西，所以我们可以在括号中为参数指定一个自定义的正则：

```js
const routes = [
  // /:orderId -> 仅匹配数字
  { path: '/:orderId(\\d+)' },
  // /:productName -> 匹配其他任何内容
  { path: '/:productName' },
]
```

现在，转到 `/25` 将匹配 `/:orderId`，其他情况将会匹配 `/:productName`。`routes` 数组的顺序并不重要!

> 确保**转义反斜杠( `\` )**，就像我们对 `\d` (变成`\\d`)所做的那样，在 JavaScript 中实际传递字符串中的反斜杠字符。

### 可重复的参数

如果你需要匹配具有多个部分的路由，如 `/first/second/third`，你应该用 `*`（0 个或多个）和 `+`（1 个或多个）将参数标记为可重复：

```js
const routes = [
  // /:chapters ->  匹配 /one, /one/two, /one/two/three, 等
  { path: '/:chapters+' },
  // /:chapters -> 匹配 /, /one, /one/two, /one/two/three, 等
  { path: '/:chapters*' },
]
```

这将为你提供一个参数数组，而不是一个字符串，并且在使用命名路由（将在下面介绍）时也需要你传递一个数组：

```js
// 给定 { path: '/:chapters*', name: 'chapters' },
router.resolve({ name: 'chapters', params: { chapters: [] } }).href
// 产生 /
router.resolve({ name: 'chapters', params: { chapters: ['a', 'b'] } }).href
// 产生 /a/b

// 给定 { path: '/:chapters+', name: 'chapters' },
router.resolve({ name: 'chapters', params: { chapters: [] } }).href
// 抛出错误，因为 `chapters` 为空 
```

这些也可以通过在**右括号后**添加它们与自定义正则结合使用：

```js
const routes = [
  // 仅匹配数字
  // 匹配 /1, /1/2, 等
  { path: '/:chapters(\\d+)+' },
  // 匹配 /, /1, /1/2, 等
  { path: '/:chapters(\\d+)*' },
]
```

### 可选参数

你也可以通过使用 `?` 修饰符(0 个或 1 个)将一个参数标记为可选：

```js
const routes = [
  // 匹配 /users 和 /users/posva
  { path: '/users/:userId?' },
  // 匹配 /users 和 /users/42
  { path: '/users/:userId(\\d+)?' },
]
```

请注意，`*` 在技术上也标志着一个参数是可选的，**但 `?` 参数不能重复**。

## 嵌套路由

一些应用程序的 UI 由多层嵌套的组件组成。在这种情况下，URL 的片段通常对应于特定的嵌套组件结构，例如：

```sh
/user/johnny/profile                     /user/johnny/posts
+------------------+                  +-----------------+
| User             |                  | User            |
| +--------------+ |                  | +-------------+ |
| | Profile      | |  +------------>  | | Posts       | |
| |              | |                  | |             | |
| +--------------+ |                  | +-------------+ |
+------------------+                  +-----------------+
```

![image-20211019183746952](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211019183746952.png)

通过 Vue Router，你可以使用嵌套路由配置来表达这种关系。

接着上节创建的 app ：

```html
<div id="app">
  <router-view></router-view>
</div>
```

```js
const User = {
  template: '<div>User {{ $route.params.id }}</div>',
}

// 这些都会传递给 `createRouter`
const routes = [{ path: '/user/:id', component: User }]
```

这里的 `<router-view>` 是一个顶层的 `router-view`。它渲染顶层路由匹配的组件。同样地，一个被渲染的组件也可以包含自己嵌套的 `<router-view>`。例如，如果我们在 `User` 组件的模板内添加一个 `<router-view>`：

```js
const User = {
  template: `
    <div class="user">
      <h2>User {{ $route.params.id }}</h2>
      <router-view></router-view>
    </div>
  `,
}
```

要将组件渲染到这个嵌套的 `router-view` 中，我们需要在路由中配置 `children`：

```js
const routes = [
  {
    path: '/user/:id',
    component: User,
    children: [
      {
        // 当 /user/:id/profile 匹配成功 
        // UserProfile 将被渲染到 User 的 <router-view> 内部
        path: 'profile',
        component: UserProfile,
      },
      {
        // 当 /user/:id/posts 匹配成功
        // UserPosts 将被渲染到 User 的 <router-view> 内部
        path: 'posts',
        component: UserPosts,
      },
    ],
  },
]
```

**注意，以 `/` 开头的嵌套路径将被视为根路径。这允许你利用组件嵌套，而不必使用嵌套的 URL。**

如你所见，`children` 配置只是另一个路由数组，就像 `routes` 本身一样。因此，你可以根据自己的需要，不断地嵌套视图。

此时，按照上面的配置，当你访问 `/user/eduardo` 时，在 `User` 的 `router-view` 里面什么都不会呈现，因为没有匹配到嵌套路由。也许你确实想在那里渲染一些东西。在这种情况下，你可以提供一个空的嵌套路径：

```js
const routes = [
  {
    path: '/user/:id',
    component: User,
    children: [
      // UserHome will be rendered inside User's <router-view>
      // when /user/:id is matched
      // 当 /user/:id 匹配成功
      // UserHome 将被渲染到 User 的 <router-view> 内部
      { path: '', component: UserHome },

      // ...其他子路由
    ],
  },
]
```

这个例子的 demo 可以在[这里](https://codesandbox.io/s/nested-views-vue-router-4-examples-hl326?initialpath=%2Fusers%2Feduardo)找到。

## 命名路由（推荐写法）

除了 `path` 之外，你还可以为任何路由提供 `name`。这有以下优点：

- 没有硬编码的 URL
- `params` 的自动编码/解码。
- 防止你在 url 中出现打字错误。
- 绕过路径排序（如显示一个）

```js
const routes = [
  {
    path: '/user/:username',
    name: 'user',
    component: User
  }
]
```

要链接到一个命名的路由，可以向 `router-link` 组件的 `to` 属性传递一个对象：

```html
<router-link :to="{ name: 'user', params: { username: 'erina' }}">
  User
</router-link>
```

这跟代码调用 `router.push()` 是一回事：

```js
router.push({ name: 'user', params: { username: 'erina' } })
```

在这两种情况下，路由将导航到路径 `/user/erina`。

### 嵌套命名视图

我们也有可能使用命名视图创建嵌套视图的复杂布局。这时你也需要命名用到的嵌套 `router-view` 组件。我们以一个设置面板为例：

```
/settings/emails                                       /settings/profile
+-----------------------------------+                  +------------------------------+
| UserSettings                      |                  | UserSettings                 |
| +-----+-------------------------+ |                  | +-----+--------------------+ |
| | Nav | UserEmailsSubscriptions | |  +------------>  | | Nav | UserProfile        | |
| |     +-------------------------+ |                  | |     +--------------------+ |
| |     |                         | |                  | |     | UserProfilePreview | |
| +-----+-------------------------+ |                  | +-----+--------------------+ |
+-----------------------------------+                  +------------------------------+
```

- `Nav` 只是一个常规组件。
- `UserSettings` 是一个视图组件。
- `UserEmailsSubscriptions`、`UserProfile`、`UserProfilePreview` 是嵌套的视图组件。

**注意**：*我们先忘记 HTML/CSS 具体的布局的样子，只专注在用到的组件上。*

`UserSettings` 组件的 `<template>` 部分应该是类似下面的这段代码:

```html
<!-- UserSettings.vue -->
<div>
  <h1>User Settings</h1>
  <NavBar />
  <router-view />
  <router-view name="helper" />
</div>
```

那么你就可以通过这个路由配置来实现上面的布局：

```js
{
  path: '/settings',
  // 你也可以在顶级路由就配置命名视图
  component: UserSettings,
  children: [{
    path: 'emails',
    component: UserEmailsSubscriptions
  }, {
    path: 'profile',
    components: {
      default: UserProfile,
      helper: UserProfilePreview
    }
  }]
}
```

## 重定向和别名

### 重定向

重定向也是通过 `routes` 配置来完成，下面例子是从 `/a` 重定向到 `/b`：

```js
const routes = [{ path: '/home', redirect: '/' }]
```

重定向的目标也可以是一个命名的路由：

```js
const routes = [{ path: '/home', redirect: { name: 'homepage' } }]
```

甚至是一个方法，动态返回重定向目标：

```js
const routes = [
  {
    // /search/screens -> /search?q=screens
    path: '/search/:searchText',
    redirect: to => {
      // 方法接收目标路由作为参数
      // return 重定向的字符串路径/路径对象
      return { path: '/search', query: { q: to.params.searchText } }
    },
  },
  {
    path: '/search',
    // ...
  },
]
```

请注意，**[导航守卫](https://next.router.vuejs.org/zh/guide/advanced/navigation-guards.html)并没有应用在跳转路由上，而仅仅应用在其目标上**。在下面的例子中，在 `/home` 路由中添加 `beforeEnter` 守卫不会有任何效果。

在写 `redirect` 的时候，可以省略 `component` 配置，因为它从来没有被直接访问过，所以没有组件要渲染。唯一的例外是[嵌套路由](https://next.router.vuejs.org/zh/guide/essentials/nested-routes.html)：如果一个路由记录有 `children` 和 `redirect` 属性，它也应该有 `component` 属性。

### 相对重定向

也可以重定向到相对位置：

```js
const routes = [
  {
    path: '/users/:id/posts',
    redirect: to => {
      // 方法接收目标路由作为参数
      // return 重定向的字符串路径/路径对象
    },
  },
]
```

### 别名

重定向是指当用户访问 `/home` 时，URL 会被 `/` 替换，然后匹配成 `/`。那么什么是别名呢？

将 `/` 别名为 `/home`，意味着当用户访问 `/home` 时，URL 仍然是 `/home`，但会被匹配为用户正在访问 `/`。

上面对应的路由配置为：

```js
const routes = [{ path: '/', component: Homepage, alias: '/home' }]
```

通过别名，你可以自由地将 UI 结构映射到一个任意的 URL，而不受配置的嵌套结构的限制。使别名以 `/` 开头，以使嵌套路径中的路径成为绝对路径。你甚至可以将两者结合起来，用一个数组提供多个别名：

```js
const routes = [
  {
    path: '/users',
    component: UsersLayout,
    children: [
      // 为这 3 个 URL 呈现 UserList
      // - /users
      // - /users/list
      // - /people
      { path: '', component: UserList, alias: ['/people', 'list'] },
    ],
  },
]
```

如果你的路由有参数，请确保在任何绝对别名中包含它们：

```js
const routes = [
  {
    path: '/users/:id',
    component: UsersByIdLayout,
    children: [
      // 为这 3 个 URL 呈现 UserDetails
      // - /users/24
      // - /users/24/profile
      // - /24
      { path: 'profile', component: UserDetails, alias: ['/:id', ''] },
    ],
  },
]
```

## 路由组件传参

### Views往Router传参

我们一个路由在跳转到另外一个路由的希望它给我们传递消息

第一种方式是配置动态路由

传递参数主要有两种类型: params和query

**params的类型:**

- 配置路由格式: **/router/:id**

- 传递的方式:**在path后面跟上对应的值**

- 传递后形成的路径: **/router/123,/router/abc**

**query的类型:**

- 配置路由格式: **/router,也就是普通配置**
- 传递的方式:**对象中使用query的key作为传递方式**
- 传递后形成的路径: **/router?id=123,/router?id=abc**



1. **用`router-link :to=`来传**

```vue
<template>
  <div id="app">
    <router-link :to="'/user/'+useId">用户</router-link>
    <router-link :to="{path:'/profile',query:{name:'why',age:18}}">档案</router-link>
  </div>   
</template>

<script>
export default {
  name: 'App',
  data() {
    return {
      useId: 'zhangsan',}
  }
}
</script>
```

2. **用@click来传(this.$router.push）**

```vue
<template>
  <div id="app">
    <button @click="userClick"></button>
    <button @click="profileClick"></button>
    <button @click="nextfileClick"></button>
  </div>
</template>

<script>
export default {
  name: 'App',
  data() {
    return {
      useId: 'zhangsan',}
  },
  methods:{
    userClick(){
      return this.$router.push('/user/'+this.useId)
    },
    profileClick(){
      return this.$router.push({
        path: '/profile',
        query: {
          name:'kobe',
          age:18,
          height:1118
        }
      })
    },
    profileClick(){
      return this.$router.push({
        path: '/profile',
        parmas: {
          name:'kobe',
          age:18,
          height:1118
        }
      })
    }
  }
}
</script>
```

我们通过对比发现我们的传对象下，params和query几乎一致

### 布尔模式

当 `props` 设置为 `true` 时，`route.params` 将被设置为组件的 props。

在这基础上，我们可以这样编写我们的代码

### 将 props 传递给路由组件（推荐原因）

在你的组件中使用 `$route` 会与路由紧密耦合，这限制了组件的灵活性，因为它只能用于特定的 URL。虽然这不一定是件坏事，但我们可以通过 `props` 配置来解除这种行为：

我们可以将下面的代码

```js
const User = {
  template: '<div>User {{ $route.params.id }}</div>'
}
const routes = [{ path: '/user/:id', component: User }]
```

替换成

```js
const User = {
  props: ['id'],
  template: '<div>User {{ id }}</div>'
}
const routes = [{ path: '/user/:id', component: User, props: true }]
```

这允许你在任何地方使用该组件，使得该组件更容易重用和测试。

当前端通过params来传对象的时候

```js
 params: {
    	user: {
    		name: '小明',
        	age: 18,
        	gender: '男',
    	}
}
```

我们则变成

```js
const User = {
  props: ['user'],
  template: `<div>User {{user.name}}</div>
    		<div>User {{user.age}}</div>
			<div>User {{user.gender}}</div>`
}
const routes = [{ path: '/user/:id', component: User, props: true }]
```

### 命名视图（进阶）

对于有命名视图的路由，你必须为每个命名视图定义 `props` 配置：

```js
const routes = [
  {
    path: '/user/:id',
    components: { default: User, sidebar: Sidebar },
    props: { default: true, sidebar: false }
  }
]
```

### 对象模式

当 `props` 是一个对象时，它将原样设置为组件 props。当 props 是静态的时候很有用。

```js
const routes = [
  {
    path: '/promotion/from-newsletter',
    component: Promotion,
    props: { newsletterPopup: false }
  }
]
```

### 函数模式

你可以创建一个返回 props 的函数。这允许你将参数转换为其他类型，将静态值与基于路由的值相结合等等。

```js
const routes = [
  {
    path: '/search',
    component: SearchUser,
    props: route => ({ query: route.query.q })  //route.query.q=vue
  }
]
```

URL `/search?q=vue` 将传递 `{query: 'vue'}` 作为 props 传给 `SearchUser` 组件。

请尽可能保持 `props` 函数为无状态的，因为它只会在路由发生变化时起作用。如果你需要状态来定义 props，请使用包装组件，这样 vue 才可以对状态变化做出反应。

# 进阶

## vue-router导航守卫

要求：

- 点到首页，则标题是首页
- 点到哪就去标题就是对应的什么

如果是以前只能靠create函数来改变，现在我们用导航守卫



为什么：

我们来考虑一个需求:在一个SPA应用中,如何改变网页的标题呢?

- 网页标题是通过<title>来显示的,但是SPA只有一个固定的HTML，切换不同的页面时,标题并不会改变.但是我们可以通过JavaScript来修改<title>的内容.`window.document.title = '新的标题'.`

- 那么在Vue项目中,在哪里修改?什么时候修改比较合适呢?

`index.js`

```js
//配置路由相关的信息
import VueRouter from 'vue-router'
import Vue from 'vue'
//1.通过Vue.use(插件）,安装插件
Vue.use(VueRouter)

//2.创建VueRouter对象
const routes = [
  {
    path: '',
    redirect: '/home'
  },
  {
    path: '/user/:userId',
    component: () => import('../components/User'),
    meta:{
      title:'真不错'
    },
  },
  {
    path: '/profile',
    component: () => import('../components/profile'),
    meta:{
      title:'档案'
    },
  },
  {
    path: '/home',
    component: () => import('../components/Home'),
    meta:{
      title:'首页'
    },
    children: [{
      path: '',
      redirect: 'news'
    },
      {
        path: 'news',
        component: () => import('../components/New'),
        meta:{
          title:'新闻'
        },
      },
      {
        path: 'message',
        component: () => import('../components/Message'),
        meta:{
          title:'信息'
        },
      }
    ]
  },
  {
    path: '/about',
    component: () => import('../components/About')
  }
]

const router = new VueRouter({
  //配置路径和组件的应用关系
  routes,
  mode: 'history'
})
router.beforeEach((to, from, next) => {
  document.title = to.matched[0].meta.title
  next()
})
//3.将router对象传到我们Vue的
export default router

```

- 补充一:如果是后置钩子,也就是`afterEach`,不需要主动调用next()函数.

```js
router.afterEach((to, from) => {
   
 
to: Route，代表要进入的目标，它是一个路由对象
 
from: Route，代表当前正要离开的路由，同样也是一个路由对象
 
 
 
// do someting
 

 
});
```

- 补充二:上面我们使用的导航守卫,被称之为**全局守卫.**
  - 路由独享的守卫.
  - 组件内的守卫.


## keep-alive

每次都会创建新组件,keep-alive 是 Vue内置的一个组件，可以使被包含的组件保留状态，或避免重新渲染。

router-view也是一个组件，如果直接被包在keep-alive里面，所有路径匹配到的视图组件都会被缓存︰

为了不浪费资源可以

```vue
    <keep-alive>
      <RouterView></RouterView>
    </keep-alive>
```

来保持我们的活跃状态，用了Vue会调用以下函数

```js
activated(){
   this.$router.push(this.path); 
}
deactivated(){
 
}
beforeRouteLeave(){
  this.path = this.$route.path
}
```

keep-alive是Vue内置的一个组件，可以使被包含的组件保留状态，或避免重新渲染。它们有两个非常重要的属性:

- include -字符串或正则表达，只有匹配的组件会被缓存
- exclude -字符串或正则表达式，任何匹配的组件都不会被缓存

> 排除的值是被导出的name，注意如果有多个，我们我们用逗号分割，而且不加空格

## 懒加载

官方给出了解释:

- 当打包构建应用时，Javascript包会变得非常大，影响页面加载。
- 如果我们能把不同路由对应的组件分割成不同的代码块，然后当路由被访问的时候才加载对应组件，这样就更加高效了

官方在说什么呢?

- 首先,我们知道路由中通常会定义很多不同的页面.
- **这个页面最后被打包在哪里呢?一般情况下，是放在一个js文件中.口但是,页面这么多放在一个js文件中,必然会造成这个页面非常的大.**
- **如果我们一次性从服务器请求下来这个页面,可能需要花费一定的时间,甚至用户的电脑上还出现了短暂空白的情况.**

如何避免这种情况呢?

- 使用路由懒加载就可以了.路由懒加载做了什么?
- **路由懒加载的主要作用就是将路由对应的组件打包成一个个的js代码块.**
- **只有在这个路由被访问到的时候,才加载对应的组件**

```js
() => import('')
```

