# 开发标准

## 命名
**不使用不常见缩写和拼音**  

1. 常量: 大写字母加下划线
2. 变量: 小写字母加下划线(包括类属性)
3. 类名: 大驼峰
4. 函数名: 小驼峰(包括类方法)

## 开发格式

### 图像类
**继承`pygame.sprite.Sprite`**
包括UI类和角色类

#### 类属性
##### 内部
1. 默认位置
2. 图像颜色(可选)
3. 图像尺寸
4. 速度(可选)

##### 示例
```python3
class NewSprite(pygame.sprite.Sprite):
	pos = 100, 100
	color = 'white'
	size = 100, 100
	speed = 100
```

#### `__init__()`方法
##### 参数
1. `game: object`游戏主类
2. `*groups`精灵组

##### 内部
1. `super().__init__(*groups)`初始化父类
2. 定义
	1. `self.image`图像, 并对其实施必要的初始化
	2. `self.rect`位置大小, 并设置默认位置

##### 示例
```python3
	def __init__(self, game: object, *groups) -> None:
		super().__init__(*groups)
		
		self.image = pygame.Surface(size=self.size)
		self.image.fill(self.color)
		
		self.rect = self.image.get_rect()
		self.rect.x, self.rect.y = self.pos
```

#### `update()`方法
##### 参数
1. `*args`和`**kwargs`

##### 内部
1. 监控键盘(可选)
2. 更新

##### 示例
```python3
	def update(self, *args, **kwargs) -> None:
		speed = self.speed * self.game.delta_time
		key_pressed = pygame.key.get_pressed()
		
		if key_pressed[pygame.K_w]:
			self.rect.y -= speed
		if key_pressed[pygame.K_s]:
			self.rect.y += speed
		if key_pressed[pygame.K_a]:
			self.rect.x -= speed
		if key_pressed[pygame.K_d]:
			self.rect.x += speed
```

#### `draw()`方法
*此函数可定义为空函数, 但不能没有*

##### 内部
1. 绘制角色的附有图像(可选)

##### 示例
```python3
	def draw(self) -> None:
		pygame.draw.circle(surface=self.game.screen,
						   color=self.color,
						   center=self.pos,
						   radius=30)
```