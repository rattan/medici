## Medici packet declaration
### Protocol version 
 - 0

### Header
 - unsigned Integer
 - 4 byte
 - fixed size

|bit index|MSB(31st)|16-30  |0-15   |
|-|-|-|-|
|Value|0-1|0-32767|0-65535|

|MSB|Description|
|-|-|
|0|General. send data|
|1|Request. request to general response to target|

### Body
 - char stream
 - mutable

|Index(Header 16-30)|operation|Name|Description|Size|Type|Detail|
|-|-|-|-|-|-|-|
|0|request/Send|ping||0||check keep alive, delay check and so on|
|1|request/Send|protocol version||4|int|check for protocol version|
|2|request/Send|app version||4|int|check for application version|
|3|request/Send|uuid||16|Uuid|check for unique id|
|4|request/Send|os||4|int|check for operating system|
|5|request/Send|name||@|string|check for user name|
|6|request/Send|ip address||4|int|check for ip address|
|7|request/Send|display||16+@|Display list||
|8|request/Send|config||36+@|Config||
||||||||
|16|Send|mouse move||8|Point||
|17|Send|mouse button||4|int||