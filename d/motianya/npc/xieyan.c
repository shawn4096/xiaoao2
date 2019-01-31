// xieyan.c
//by sohu@xojh

#include <ansi.h>

inherit NPC;

string ask_lingp();
string ask_bizhen();
//int accept_object(object me, object ob);

#define XKX_QUEST1 "quest/������/Ħ����/"
#define XKX_QUEST2 "quest/������/������/"

void create()
{
        seteuid(getuid());
        set_name("л�̿�", ({ "xie yanke", "xie" }));
        set("long", @LONG
Ħ���ʿл�̿������µ�һ���ˣ��书��ǿ������ɢ��
��������ö�����Կ�������ӵ�д���������κ�Ը����
LONG );
        set("nickname", HIG "Ħ���ʿ" NOR);
        set("gender", "����");
        set("age", 71);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("qi", 45000);
        set("max_qi", 45000);
        set("jing", 6500);
        set("max_jing", 6500);
        set("neili", 35000);
        set("max_neili", 35000);
        set("max_jingli", 8000);
        set("jingli", 8000);
        set("eff_jingli", 8000);
        set("jiali", 220);

        set("combat_exp", 15500000);

        set_skill("force", 500);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("strike", 500);
        set_skill("luohan-fumogong", 500);
        set_skill("shexing-lifan", 500);
        set_skill("bizhen-qingzhang", 500);
        set("quest/xkx/lsfmst/luohan", 1);
        map_skill("force", "luohan-fumogong");
        map_skill("dodge", "shexing-lifan");
        map_skill("strike", "bizhen-qingzhang");
        map_skill("parry", "bizhen-qingzhang");

        prepare_skill("strike", "bizhen-qingzhang");
        set("chat_chance_combat", 80);
        
		set("chat_msg_combat", ({
		(: exert_function, "luohan" :),
		(: perform_action, "strike.pengpai" :),
		//(: perform_action, "hand.qianshou" :),
		//(: perform_action, "leg.ruying" :),
	}));

        set("inquiry", ([
               "��������" : (: ask_bizhen :),
               // "����"     : (: ask_me :),
               // "����"     : (: ask_me :),
              //  "����"     : (: ask_me :),
               // "������"   : "��ö���������Ѿ��ջ�,����һöʧ�佭��������������࣬�����ȥ�Գ�֮���￴����",
			   "������"     : (: ask_lingp :),
			  // "ʯ�������"     : (: ask_bangzhu :),

                "ʯ����"   : "�������Ǹ��׳ջ�û��ô��",
        ]));
        setup();
        carry_object("/clone/armor/cloth")->wear();
}
void init()
{
	if (this_player()->query(XKX_QUEST2+"givexieling"))
	{
		command("nod "+this_player()->query("id"));
	}
}
string ask_lingp()
{
	object me;
	me=this_player();
	command("say ��Ħ���ʿл�̿�һ����һ�ԾŶ�");
	command("say ŵ������ֻ�û����Ħ���ʿ�첻�˵��¡�");
	command("say ��ʮ��ǰ������������ö�����Ҳ��������ŵ");
	command("say ������˭��ֻҪ�����������ң��Ҷ����Ӧ������һ����");
	command("say ����Ϊֹ���Ѿ���������ö�������ˣ��������һöû���ջ�");
	command("say ��Ħ���ʿл�̿�������ŵ���ˣ���ö������һ�첻������һ����ʳ�Ѱ�");
	command("say ��һö�����֪������˭�����У�����");

	if (me->query(XKX_QUEST2+"start")
		&& objectp(present("xuantie lingp",me))
		&& me->query(XKX_QUEST2+"findxtl"))
	{
		command("nod "+me->query("id"));
		command("say ����糾���ͣ��Ҵ����ˣ�һ���˳������ӣ��ѵ���������ô��\n");
		me->set_temp(XKX_QUEST2+"meetxie",1);
	}
	return "��ö�����������������ˣ���֪��ʱ���ջ�����\n";
	
}

int accept_object(object me, object ob)
{				

        //��������bug����ֹ����
//			write("11");

		if (ob->query("id") == "xuantie lingp"
			//&&ob->query("name") =="��������" 
			&&ob->query("owner")==me->query("id")
			&&me->query(XKX_QUEST2+"start")
			&&me->query(XKX_QUEST2+"findxtl")
			&&me->query_temp(XKX_QUEST2+"meetxie"))
		{
//			write("22");
			command("ah");
			command("say �ҵĵ���ö�����");
			command("say ������������ö��������ǵõ�����������˶��ɸ�����һ��Ҫ��");
			command("say ��л�̿Ͷ���������������Ҫ��");
			command("say ����ö�������Ѿ������ջ��ˣ��Ͳ������һö�ˣ�û�뵽��Ȼ������õ��ˡ�");
			command("say �ҷǳ������㣬���Ժ����������Ħ�����ˡ�");

			command("say ����ʲô�������˵�ɡ�");
			command("smile "+me->query("id"));
			destruct(ob);
			//me->delete_temp(XKX_QUEST2+"meetxie");
			me->set_temp(XKX_QUEST2+"givexieling",1);
			me->set(XKX_QUEST2+"givexieling",1);
			message_vision(HBYEL+HIW"\n\n��ϲ$N����ˡ������С�����ϵ�ж�֮��������ƪ��\n"NOR,me);
			return 1;

		}else
		return 0;
}

string ask_bizhen()
{
		object me;
		int i,j;
		me=this_player();
		message_vision(HIM"��С������Ĵս�л�̿ͣ��������ģ�˵����������Ħ���ʿл�̿͵ı��������������¡�\n"NOR,me);
		message_vision(HIM"����ѧ���ž�ѧ����֪���Ƿ�Ը����ң�\n"NOR,me);
        if (!me->query(XKX_QUEST2+"givexieling"))
		{
            return "û�������ڣ��Ǽ鼴��������ʶ��ô��\n";

		}
		if (me->query("quest/xkx/bzqz/pass")) 
		{
			me->set("title",HIC"�������ƴ���"NOR);
            return "�̵ܽ��Ѿ������ˣ��������Ҹ��\n";
		}
        if (me->query_skill("force",1)<350)
                return "��Ļ����ڹ�̫�ͣ�����350��ѧ��������Ҳû�ã�\n";
		if (me->query_skill("strike",1)<350)
                return "��Ļ����Ʒ�̫�ͣ�����350��ѧ��������Ҳû�ã�\n";
        
		if (time()-me->query("quest/xkx/bzqz/time")<86400)
		{
			return "������Ҳ̫�ڿ���ˣ�\n";
		}
	

        message_vision(HIW "$n" HIW "��Цһ����˫�ƶ�Ȼ����"
                       "��һ����Ȧ�����ƶ�������ʱһ����ӿ��"
                       "�ȵľ����粨��һ����" HIW "ӿ����\n$N"
                       HIW "�󺧣�Ӳ������һ�У�ֻ����Ϣ����"
                       "��ȫ�������Ҫɢ��һ�㡣ͻȻĿ��һ��"
                       "���ƺ�������ʲô��\n" NOR,
                       me, this_object());

        command("grin");
		
    i = 25;
    if(me->query("m-card-vip")) i =  23;
    if(me->query("y-card-vip")) i =  20;
    if(me->query("buyvip"))     i =  18;
    i=random(i);
	j=random(me->query("kar"));
	command("say ���ű��������������־�ѧ���������Ǿ����ɺ��������ƣ������ߴ�ֱ���͹�Ѩ���������Ʒ��ľ�Ҫ���ڡ�\n");
	command("pat "+me->query("id"));
	if( i<2
		&& me->query("kar")<31
		&& j > 27 ) 
	{
		tell_object(me,HIY"\n������л�̿͵�����ָ�㣬�����������Լ�����Ħ�����Ƶ������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㵤�������������ߣ���Ȼ��˳�м����ϣ�������͹�Ѩ,˫�����������ޱȡ�\n"
							"��Ȼ��һ�ɾ����𵴣��糤����ӣ����ϲ�������ʱͻ���͹�Ѩ�������ơ�\n"
						 +"����������������<��������>���������÷��š����д�ϲ��\n"NOR);
		me->set("quest/xkx/bzqz/pass",1);

		log_file("quest/xkxbizhen", sprintf("%8s(%8s) ʧ��%d�κ�ѧ���������ƾ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/xkx/bzqz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		command("haha"+me->query("id"));		
		me->improve_skill("bizhen-qingzhang",1000);
		return "��ϲ����Ħ���±������ƾ����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/xkxbizhen", sprintf("%8s(%8s) ���ܱ������ƾ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/xkx/bzqz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"������л�̿͵�ָ�㣬���Ƕ�Ħ�����Ʊ������Ƶİ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/xkx/bzqz/fail",1);
		me->set("quest/xkx/bzqz/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź�����Ħ���±�������ʧ��"+me->query("quest/xkx/bzqz/fail")+"�Ρ�\n";
	}


}
