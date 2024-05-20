# Vue项目的创建

## 初始化项目

我们的项目默认使用我们的`Vue CLI v4.5.14`输入以下指令

```npm
vue create 项目名
```

我们选择默认的`Vue3`来作为我们的使用

我们来手动配置我们的项目结构，选第三个

![image-20211028222941237](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211028222941237.png)

我们选择我们的自定义`Vue`版本，选中`Babel`和`Linter/Formatter`

![image-20211028223144476](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211028223144476.png)

![image-20211028223207530](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211028223207530.png)

我们选择标准状态下我创建我们的`Linter/Formatter`，并选择`Lint on save`

![image-20211028223453499](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211028223453499.png)

并独立放置我们的文件夹为我们的`Babel,ESLint,etc`配置config

![image-20211028223634044](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211028223634044.png)

完成安装后我们的目录结构如下：

![image-20211028223832193](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211028223832193.png)

我们可以把整个项目在`github`仓库进行托管

我们在`github`进行对应的仓库建立以后，里面给出提示可以快速引入代码，可以使用对应的指令

> `github`在最近的更新中，我们的密码变成了对应的token，记得申请

## 划分目录

我们的`scr`文件夹下

**设置新的文件夹分别是`common` 、`network`、 `router`、 `store`、`views`五个文件夹**

- `common` 是我们该项目的公用的`js`，如我们的`const.js`、 `utils.js`、 `mixin.js`三个文件，分别是来负责我们的公共常量，工具类，混入相关的
- `network`里面有对应的`request.js`
- `router`里面有对应的`index.js`
- `store`里面有对应的`index.js`
- `views`里面有我们的对应的不同页面的视图

> 我们的不同视图创建不同文件夹放在不同类型视图

**我们在原有的`assets`下面创建`css`、`img`**

- `assets`下面`css`有`base.css`、`normalize.css`，其中我们的`normalize.css`是我们默认的，可以在`github`找到

```css
@import "normalize.css";
```

> 我们把对应的`normalize.css`导入我们的`base.css`，最后引用我们的样式的时候直接使用我们的`base.css`

- `img`又有对应的划分，比如我们的`tabbar`是一类组件，`navbar`是一类组件，就应该划分对应的文件夹

**我们的原有的`components`下面创建`common`、`content`两个文件夹**

- `common`负责我们的所有项目都可以使用的组件
- `content`是该项目特有的组件

> 两个文件下面又可以根据具体细分，例如我们主页面页面有`navbar`和`tabbar`两个组件文件夹，两个组件文件下下面又有对应的多个组件，我们可以编写对应的js，把所有Vue组件导入对应的js，再将js导出

```js
import Swiper from './Swiper'
import SwiperItem from './SwiperItem'

export {
  Swiper, SwiperItem
}
```

## 配置`vue.config.js`

配置完我们的文件夹分类以后，我们开始对各个文件夹对应设置我们的别名

这样我们可以快速调用不同文件下的资源

```js
module.exports = {
  lintOnSave: false,
  configureWebpack:{
    resolve:{
      alias:{
        assets:'@/asset',
        common:'@/common',
        components:'@/components',
        network:'@/network',
        views:'@/views',
      }
    }
  }
}
```

## 实例化`Router`

我们的`vue-router`版本在 `^4.0.12`以后我们使用我们的Router文件时候，也发生了对应的改变

1. 安装

```sh
npm install vue-router@4
```

2. 配置

```js
import {createRouter,createWebHistory} from 'vue-router'

const routes = [{
    path:
    component: ()=>import('')
}]
const router = createRouter({
  history:createWebHistory(process.env.BASE_URL),
  routes:routes
})

router.beforeEach((to,from,next)=>{
  document.title = to.matched[0].meta.title
  next()
})
export default router

```

我们不使用全局的router而是创建对应的一个实例，最后在原始组件中引用

这里我们的路由全部利用懒加载的机制





## 实例化`store`

我们的`vue-store`版本在 `^4.0.12`以后我们使用我们的store文件时候，也发生了对应的改变

1.安装

```sh
npm install vuex@next --save
```

2.配置

```js
import { createStore } from 'vuex'

// 创建一个新的 store 实例
const store = createStore({
  state () {
    return {
      count: 0
    }
  },
  mutations: {
    increment (state) {
      state.count++
    }},
  actions: {},
  getters: {},
  modules: {}
})

export default store
```

## 配置`main.js`

我们要引用我们实例化好的`route`和`store`

```js
import { createApp } from 'vue'
import App from './App.vue'
import route from "@/router";
import store from "@/store";

createApp(App).use(route).use(store).mount('#app')
```

## 设置`App.vue`

我们的`App.vue`里面遵循简单原则，一般放在该文件导入以下东西

- <router-view/>组件
- 某些需要一直在页面上显示，**而且展示的形式不会改变的组件**
- 我们的`base.css`

如，在我们的在`Vue`学习的网上商城系统

```vue
<template>
  <div id="App">
    <router-view/>
    <maintabbar/>
  </div>
</template>

<script>


import Maintabbar from "@/components/content/MainTabBar/maintabbar";

export default {
  name: 'App',
  components: {Maintabbar}
}
</script>

<style>
@import "assets/css/base.css";
</style>
```

## 题外话：为什么分成`Views`和`components`

首先，`src/components`和文件夹都`src/views`包含Vue组件。

关键区别在于某些Vue组件充当路由*视图*。

在Vue中（通常是Vue Router处理路由时，将定义路由以切换组件中使用的当前*视图*。这些路线通常位于`src/router/routes.js`，我们可以看到以下内容：

```js
import Home from '@/views/Home.vue'
import About from '@/views/About.vue'

export default [
  {
    path: '/',
    name: 'home',
    component: Home,
  },
  {
    path: '/about',
    name: 'about',
    component: About,
  },
]
```

位于下方的组件`src/components`不太可能在一条路线中使用，而位于下方的组件`src/views`将被至少一条路线使用。

------

> Vue CLI的目标是成为Vue生态系统的标准工具基线。它可以确保各种构建工具与合理的默认设置一起顺利运行，因此您可以专注于编写应用程序，而不必花费大量时间进行配置工作。同时，它仍然可以灵活地调整每个工具的配置，而无需退出。

Vue CLI旨在快速Vue.js开发，它使事情变得简单并提供了灵活性。其目标是使具有不同技能水平的团队能够建立新项目并开始使用。

归根结底，**这取决于便利性和应用程序结构**。

- 有些人喜欢有自己的看法文件夹下`src/router`像 [**这样**](https://github.com/chrisvfritz/vue-enterprise-boilerplate/tree/master/src/router)的企业样板。
- 有人称它为*Pages*而不是*Views*。
- 有些人将所有组件都放在同一文件夹下。

## 引入`element-UI`

1. 安装

```sh
# NPM
$ npm install element-plus --save
```

2. 引入

```js
import { createApp } from 'vue'
import App from './App.vue'
import 'element-plus/dist/index.css'
import ElementPlus from 'element-plus'

createApp(App).use(ElementPlus).mount('#app')
```

