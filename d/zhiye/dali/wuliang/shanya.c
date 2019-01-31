// bbb 1997/06/11
// Modify By River 98/12
// Modify by tangfeng 2004

#include <ansi.h>
int get_object(object ob);
inherit ROOM;
#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"

string look_down();
void create()
{
	set("short", "������");
	set("long", @LONG
�߳�ʮ�������������ɽ����ĺ�ɽ���������������ɽ��أ��κ�����
�������롣��������ܲ���ɽʯ���졣�Ա߾���һ����׵�����(cliff)��
LONG
	);
	set("exits", ([
		"northwest" : __DIR__"pubu",
	]));
        set("outdoors", "����");
        set("objects", ([
           "/d/dali/wuliang/obj/yeguo" : 2,
        ]));

	set("item_desc",([
	   "cliff" : (: look_down :),
	   "down" : "�����ãã��ʲôҲ��������\n"
	]));
	setup();
}

void init()
{
	add_action("do_jump", "tiao");
        add_action("do_jump", "jump");
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int do_jump(string arg,object *obj)
{
	      object me= this_player();
        if (!arg || (arg !="down" && arg !="cliff")) return 0;
        if(sizeof(obj)){
         message_vision(HIR "$N���²�һ���գ�����������������һ���ҽУ�����ֱ׹��ȥ��\n"NOR, me);
         me->receive_wound("qi", 20);
         me->unconcious();
         me->move("/d/dali/shanlu3");
         return 1;
         }
	      if(me->query_condition("killer")) return 0;
        if (me->query(QUESTDIR1+"start") 
           && me->query(QUESTDIR1+"over"))
        {
	       message_vision(HIR "$N���²�һ���գ�����������������һ���ҽУ�����ֱ׹��ȥ��\n" 
                            "$N׹�°����ɣ�ײ���±�һ�ù����ϣ����˼�������׹�ľ���ȴҲ���ˡ�\n" NOR, me);
         me->move(__DIR__"bankong");
         tell_object(me,HIY"\n���Ѳ��ǵ�һ����Ծ������Σ�գ���ʵ���翴���˷�������һ��������\n"
                           "ץס���ɣ��ٴν�����һ�������Ѿ���ȫ����һ���������㻺��Ծ��������\n"NOR);
         me->move(__DIR__"banshan1");
	       return 1;
         }
        if ((me->query(QUESTDIR1+"start") && (random((int)me->query("kar")) >8))
        ||(me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"jianying")) 
        || (random((int)me->query("kar")) >20)
        || me->query("marks/xiaoyao")
)
        {
	       message_vision(HIR "$N���²�һ���գ�����������������һ���ҽУ�����ֱ׹��ȥ��\n" 
         "$N׹�°����ɣ�ײ���±�һ�ù����ϣ����˼�������׹�ľ���ȴҲ���ˡ�\n" NOR, me);
         me->move(__DIR__"bankong");
	       return 1;
         }
         message_vision(HIR "$N���²�һ���գ�����������������һ���ҽУ�����ֱ׹��ȥ��\n"NOR, me);          
         me->receive_wound("qi", 20);
         me->unconcious();
         me->move("/d/dali/shanlu3");
         return 1;
}

string look_down()
{
	return  "����(down)��ɲ⣬�����������ף������Ҫ��ɱ���⵽�Ǹ��õط���\n";
}

/*

//���ϣ���Ӱ���ַ�������
int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);


	
	if((local[2] < 2 || local[2] >= 23) && me->query("marks/xiaoyao")== "wait2" )
	{
		write(HIC"��һƳ�ۼ䣬��������ʯ���������вʹ�����������ȥ����Ȼ��һ�ѳ�����Ӱ\n"
		         "�ӡ�����Ӱ�и������ʺ�һ����ι⣬��˸���������߲�����\n"NOR, me);
        me->set("marks/xiaoyao","wait3");   

	}
	
	if(local[2] >= 2 && local[2] < 4 &&  me->query("marks/xiaoyao")== "wait3" )
	{
		write(HIY"��̧ͷһ����ԭ������������Ѿ��䵽�������ͱ�֮���ͱ�����һ���ף��¹�\n"
		         "�Ӷ��ױ˶���������������������вʹ������������������ڶ�����ظߴ���ʮ�ɣ�\n"
		         "���ɵ����´��棬��Ҫ��ȥ�������ס�\n"NOR, me);
		me->delete("marks/xiaoyao");
		me->set("marks/xiaoyao","get_book");

	}

//��������ʼ�Ⱥ�
    if(local[2] >= 4 && local[2] < 18 )
		//&&  me->query("marks/xiaoyao")== "gotofind")
	{
        write(HIW"    �������£����Ʒ�ȣ������ϱ����������ͱڣ����޳�·����������һ�ԴԵĲ軨��ҡҷ���ˡ���\n"NOR, me);
        me->set("marks/xiaoyao","wait");
		me->start_busy(2);
	}
	
	if(local[2] >= 18 && local[2] < 21 
		&&  me->query("kar")>27
		&&  me->query("marks/xiaoyao")== "wait" )
	{
		write(HIC"    ��վ��������̧ͷֻ��������Բ������ں����ϱ���ͬ����һ�����һ�㣬��\n"
                 "��˳�ź���һ·��չ��ȥ��ͻȻȫ��һ��ֻ����������Ϻ�Ȼ�и���Ӱ�ڻζ���\n"NOR, me);
       me->set("marks/xiaoyao","wait1");         
	}

	if(local[2] >= 21 && local[2] < 23 &&  me->query("marks/xiaoyao")== "wait1" )
	{
		write(HIM"    ��ع�������ֻ�����Сʯ����Ҳ�и���Ӱ��ֻ�����μ�С��Ӱ��ҲŨ�Ķࡣ��ʱ��\n"
		         "Ȼ���򣺡�ԭ�������Ƚ��ҵ�Ӱ��ӳ�����Сʯ���ϣ���ӳ������Ĵ�ʯ���ϣ�����ȷ��\n"
		         "�����������轣����Ӱӳ����� ���������������������������֮�ʣ��漴�����㵸��\n"
		         "ȭ�����,���������������Ҳ���¶���������赡���Ӱ�����϶�����������ʾ�����书��\n"
		         "Խ��Խ����Ȥ���̲�ס������Ц��\n"NOR, me);
                 me->set("marks/xiaoyao","wait2");   
	}


}

*/