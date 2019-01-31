// Room: /u/zqb/tiezhang/szfeng.c

inherit ROOM;

void create()
{
	set("short", "ʳָ��");
	set("long", @LONG
�����������˷嶥���Ѿ��۵����������ˡ�����ֻ������Բ�ĵط���ȴ
����Щïʢ����ľ(tree)��վ���±ߣ�һ�����Х������������һ������
���ˤ�����������ǸϿ��뿪����ĺá�
LONG
	);

        set("item_desc",([
        "tree": "����Щ���˼�ʮ��Ĳ����ɰ�,����һ��������ԼԼ�и��������������ϣ��������Ҫ������(search)��\n"
]));

	    set("no_clean_up", 0);
        set("outdoors", "tiezhang");
		set("paper",1);
	    setup();
}

void init()
{
        add_action("do_climb","climb");
        add_action("do_kan","kan");
		add_action("do_find","search");
}

int do_climb(string arg)
{
        object me;
        me=this_player();
        if (!arg || arg !="down")
         return notify_fail("��Ҫ��������? \n"); 
            write("����Ե��ʯ�ڣ�����������ȥ��\n");
            message("vision",me->name() + "������ȥ��\n", environment(me), ({me}) );
            me->move(__DIR__"juebi-5");
            message("vision",me->name() + "����������\n", environment(me), ({me}) );
         return 1;
}
int do_kan(string arg)
{
       object me = this_player();
       object weapon;
       string weapon_name;
       
       if (me->is_busy() || me->is_fighting())
             return notify_fail("����æ���أ�\n");
       if (!arg || arg !="tree")
             return notify_fail("��Ҫ��ʲô��\n");
       if (!me->query_temp("weapon"))
               return notify_fail("�������ô����? \n");
       if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "axe") 
               return notify_fail("���õı������ԡ�\n");   
       if (!me->query_skill("axe",1))
               return notify_fail("�㲻�����ּ��ܡ�\n");
       if (me->query("neili") <100)
               return notify_fail("������������ˡ�\n");
       if (me->query_skill("axe",1) < 30) 
               return notify_fail("��Ļ�������̫���ˣ��޷�ʹ�ø��ӿ�����\n");
        weapon_name = weapon->query("name");
       if (me->query_skill("axe",1) > 100)
               return notify_fail("���������"+ weapon_name +",�����ɵذ�һ�ô��������ˡ�\n");
       if (me->query("jing") < 5 || me->query("neili") < 10 ){
               message_vision("����һ�ô�������$N���ϣ�$Nһ���ӱ������˹�ȥ��\n", me);
               me->unconcious();
               return 1;
        }
//        message("vision", me->name() + "��������"+ weapon_name +"����������һ���µؿ�ȥ��\n",environment(me), ({me}));��
        write("���������"+ weapon_name +",��������һ���¿�ȥ��\n");
        me->receive_damage("jing",10);
        me->set("neili",(int)me->query("neili")-5);

        if ((int)me->query_skill("axe", 1) >= 30 && (int)me->query_skill("axe", 1) <= 100 )
        {
        me->improve_skill("axe", me->query("int"));
        tell_object(me, "��Լ֮�У����ƺ����û���������Щ�����ˡ�\n");
        }
        return 1;
}
int do_find(string arg)
{
        object me,obj;
        me=this_player();
        if (!arg || arg !="����")
            return notify_fail("��һ����ͷ���Եģ�������Ѱ��ʲô? \n"); 
        if (this_object()->query("paper")<1)
            return notify_fail("�㽫�������Ѱ�˰��죬ʲô��û���ҵ����ƺ��Ѿ�Ϊ������ȡ�ߡ� \n"); 
		if (!me->query_temp("sxb/askfu"))
		    return notify_fail("������æǰæ������У��Ա����˺�Ȼ��Ц�����������������������𣿡� \n"); 
		write("�㽫������������⣬����������Ѱһ�飬��Ȼ�������������и�С������\n");
		write("������һ�����������������������ǿ�����Ȼ���������Ͳ�������һ��С������\n");
		write("��С����������С�������ó�һ�����ᣬ��ϸչ����������Ȼ�Ǹ�д�˺ܶ������ֵ���ϵ��\n");
		//message_channel("rumor "+me->query("name")+"��Ե�ɺϷ�����Ľ����Ϯ��\n");
		obj=new("d/mr/npc/obj/shixibiao");
		obj->move(me);
		this_object()->add("paper",-1);
		me->delete_temp("sxb/askfu");
		me->set_temp("quest/mr/dzxy/getshixibiao",1);
        return 1;
}