// Room: /d/huashan/xiuxi1.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
//inherit NPC;
int do_liaoyang();
int do_kaoyan(string arg);
void create()
{
        set("short", "Ů��Ϣ��");
        set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵������������ֻ����
�����һ����ʰ����������Ĵ󴲣����ž�������˯����
LONG
        );

        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits",([
        	"north" : __DIR__"celang3",
	]));

        set("indoors", "��ɽ" );
        set("coor/x",70);
        set("coor/y",-40);
        set("coor/z",80);
		//add_action("do_liaoyuan", "liaoyang");
        setup();
}
void init()
{
	add_action("do_liaoyang", "liaoyang");
}

int do_liaoyang()
{
	
        object me = this_player();
        //if (me->query("eff_jing")= me->query("max_jing")|| me->query("eff_qi")= me->query("max_qi"))
       // 		return notify_fail("������͵���������Ͻ�ȥ������\n");
        if (me->is_busy())
                return notify_fail("����æ���أ��޷������������ˡ�\n");
        if (me->is_fighting())
                return notify_fail("������ս���У���ξ����������ˣ�\n");
        if (me->query("quest/huashan/zixia3")&& random(10)<= 6)
        {
			write(HIC"\n�����ڰ�������������,��Ȼ����ɺ�˳������˽������������ص�������һ���飬��ȻһЦ������˵�������ú���������\n"NOR);
			write(HIY"\n��������һ����Ȼ�Ǳ���������ѧ�ؼ�����ϼ��������ʱ����Сʦ�õ�һ�����⣬�������аٸн�����\n"NOR);
			write(HIR"\n�㷭����һҳ��ֻ������д����\n"NOR
			+MAG"\n�����书��������Ϊ������Ȼ������ԭΪ���ڣ�Ω���˲�����֮�������Է��������֮����\n"
			+"���Ա����Խ����Կᡢ�������������Ŷ����ң��������������������ɥ�ʶ���ʧ�������ĺݶ����١�\n"
			+"�������ߣ����ǽ���֮���⡭��������ԣ��������ƣ����걩�ᣬ����������\n"
			+"����ģ����񽬣������أ�ߵ�������ݶ���֮������С�ɡ�\n"NOR);
			message_vision(HIY"\n�����Ѹ����˶��������û�ɽ��һ�ؼ�����ϼ�ؼ�����˼ǰ������������ش��顣"NOR
				+HIR"��ѧ��"NOR+HIY"����"NOR+HIR"����ѧ����\n"NOR,me);
			add_action("do_kaoyan","answer");
			add_action("do_kaoyan","huida");
			//call_out("aoqi",5,me);
			return 1;
			
		 }
		write(HIY"������ڴ��ϣ����ڰ�������, ������Ȼ��\n"NOR);
		me->start_busy(1);
        return 1;
}

int do_kaoyan(string arg)
{
   object me=this_player();
   if (arg == "ѧ")
   {
    message_vision(HIC"\n������۾�����׼���ж��⻪ɽ��һ�ؼ���ʱ�򣬺�Ȼһ��������Ӱ������һ�������������!\n"NOR
	+HIR"\n���۵��³�һ����Ѫ����ʱ���Ե��ء��������������е��ؼ��ﳤ��ȥ��\n"NOR,me);
	me->unconcious();
	me->delete_temp("quest/huashan/zixia3");
	//write("");
	return 1;
   }
   if (arg=="��ѧ")
   {
   	
     write(HIC"\n�������ѧ����Ȼʦ��û������ѧ���Ҽ���͵ѧ�ؽ�Ϊ�������ݡ����ɷ������أ��ι�����������\n"NOR);
     write(HIR"\n�����а������������������������������[��ϼ�ؼ�]����һ�ӣ����������������Ų��߳����⡣\n"NOR);
	 me->move(__DIR__"zhengqi");
	 me->delete_temp("quest/huashan/zixia3");
	 me->set_temp("quest/huashan/zixia4",1);
	return 1;
   }
   write("\n��Ҫ�ش�ʲô��\n");
   return 1;
}
