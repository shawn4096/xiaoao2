//ljroad3.c �ּ�С·
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
    set("short", "�ּ�С·");
    set("long",@LONG
������һ��Ƭ��ɭ�֣�һ�����۵�С·��Խ��䡣������û����ɽ������
�ͱڵ�Σ�գ������ѽ�Ϊƽ̹������ľ�߳��Ƽ䣬�ֱ���һ����ɭ���¡�����
����ľ��ֱ�������ţ����й��ɣ��Ǽ�����ǰ���������ǿ��ٹ�����ʱ��ֲ��
������Ϊ��ֲ������ʱ����Ѿã��кܶ�ķ������޳�����䡣���Ҽ����ʮ
�ֺ�Ļ�ѩ���侰ʮ��׳�ۡ�
LONG);
    set("exits",([
         "southeast" : __DIR__"ljroad2",
         "southwest" : __DIR__"ljroad2a",
         "northup" : __DIR__"qianting",
    ]));
    set("coor/x",-290);
  set("coor/y",130);
   set("coor/z",90);
   set("coor/x",-290);
 set("coor/y",130);
   set("coor/z",90);
   setup();
    set("outdoors", "���̹�����");
}