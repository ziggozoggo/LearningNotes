# Docker основные команды

Материалы:
- [Плейлист по docker](https://www.youtube.com/watch?v=jVV8CVURmrE&list=PLqVeG_R3qMSwjnkMUns_Yc4zF_PtUZmB-) 

## Оглавление
- [Docker основные команды](#docker-основные-команды)
  - [Оглавление](#оглавление)
  - [Установка (Ubuntu)](#установка-ubuntu)
  - [Базовые инструменты](#базовые-инструменты)

## Установка (Ubuntu)

Установка осуществляется при помощи [официальной документации](https://docs.docker.com/engine/install/ubuntu/)

После установки проверить работу docker
```
$sudo docker run hello-world
$docker --version
$service docker status
```

Для запуска docker команд без использования прав root пользователя необходимо включить в группу docker (после добавления - перезагрузить хост)

```
$sudo usermod -aG docker my_username
```

Проверить список групп пользователя:

```
$id my_username
```

## Базовые инструменты

Контейнер запускается на основании образа (image) и активен до тех пор, пока активен процесс на контейнере.

Просмотр всех image

```
$docker images
```

Удалить образ (image)

```
$docker rmi <IMAGE ID>
```

Просмотр всех контейнеров, в т.ч. не активных

```
$docker ps -a
```

Удалить контейнер

```
$docker rm <NAME>
$docker rm <CONTAINER ID>
```

Запуск контейнера в фоновом режиме с последующим его удалением после завершения работы

```
$docker run --rm -d nginx
```

Проверить используемые контейнером ресурсы

```
$docker stats <CONTAINER ID>
```

Получить информацию о контейнере

```
$docker inspect <CONTAINER ID> 
```

Остановить контейнер и проверить его статус

```
$docker stop <CONTAINER ID>
```

**Проброс портов (port mapping)**
Шаблон: <порт сервера>:<порт образа>

```
$docker run -d --name my_nginx -p 8080:80 -p 443:443 nginx
```

Проверить что порты хоста открыты

```
$netstat -tulpen
```

Перезапуск контейнера 

```
docker restart my_nginx
```

Просмотр логов (-f включает режим обновления логов)

```
docker logs -f <CONTAINER ID>
```

Вход в консоль запущенного контейнера

```
docker exec -it <ID>|<NAME> /bin/bash
```
