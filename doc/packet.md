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
|1|request/Send|config||@|json string|send my configuration|
||||||||
|16|Send|mouse move||8|Point||
|17|Send|mouse button||4|int||