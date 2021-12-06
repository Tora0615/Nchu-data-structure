### 不等於換行符號(^\n) 則一直讀
```c
fscanf(f_write_ptr,"%[^\n]",context);
```

### 不等於空格(^ )以及不等於換行符號(^\n) 則一直讀
```c
 fscanf(f_write_ptr,"%[^ &&[^\n]]",context);
```
