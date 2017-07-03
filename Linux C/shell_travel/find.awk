#!/usr/bin/awk -f
#找到/etc/passwd里面root开头的一行
BEGIN{
      printf(">>>>>>>>>>>\n");
      FS="/"
      WHO="root"
}
{
    for(i=NF;i>0;i--){
        if($i ~ /:/)
            break
    }
    if($1 ~ /root/){
            printf("%s",WHO);
            for(i+=1;i<=NF;i++){
                    printf("/%s",$i);
                }
        printf("\n");
        }
}
END{
    }
