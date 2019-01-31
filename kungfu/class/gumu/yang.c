// yang.c ���
// By River 98.8

#include <ansi.h>
#include "yang.h"
inherit NPC;
//inherit F_MASTER;
string ask_sword();
int pfm_haichao();
int pfm_anran();
string ask_skill();
string ask_skill1();
string ask_skill2();
string ask_guojing();
string ask_huangrong();
string ask_guofu();
string ask_shunv();
int do_learn(string arg);
int ask_anranzhang();
int ask_liaoshang();
int ask_zhou();
int ask_yinggu();

void create()
{
	set_name("���",({"yang guo","yang","guo"}));
	set("title",HIW"��Ĺ����"NOR);
	set("nickname",HIY"������"NOR);
	set("long", "�������������µ���������һ�۵����ڲ�ȥһ����Ӣ�ۺ�����\n");
	set("age", 39);
	set("attitude", "friendly");
	set("gender", "����");
	set("shen", 10000);
	set("per", 36);
	set("str", 40);
	set("int", 35);
	set("con", 40);
	set("dex", 35);

        set("max_qi", 50000);
        set("max_jing", 7000);
        set("neili", 58500);
        set("eff_jingli", 7500);
        set("max_neili", 58500);
        set("jiali", 250);
        set("combat_exp", 15800000);
        set("unique", 1);

        set_skill("sword",550);

		set_skill("qimen-bagua",150);
		
set_skill("dodge",500);
        set_skill("strike",550);
        set_skill("force", 550);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);

		set_skill("yunu-jianfa", 500);
		//
set_skill("finger",140);
        set_skill("literate", 350);
        set_skill("xiantian-gong", 150);
		//
set_skill("hamagong",300);
        set_skill("medicine",120);
        //set_skill("jingmai-xue", 80);
        set_skill("yunu-shenfa", 500);
        set_skill("xuantie-jianfa", 550);
        set_skill("anran-zhang", 550);
        set_skill("quanzhen-jianfa",500);
        set_skill("tianluo-diwang", 500);
        set_skill("yunu-xinjing",550);
        set_skill("jiuyin-zhengong",220);
        set_skill("meinu-quanfa",500);

		map_skill("force", "yunu-xinjing");        
        map_skill("sword","xuantie-jianfa");
        map_skill("dodge", "yunu-shenfa");
        map_skill("parry", "anran-zhang");        
        map_skill("hand", "tianluo-diwang");
        map_skill("strike", "anran-zhang");        
        prepare_skill("strike","anran-zhang");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: exert_function, "xinjing" :),
		(: pfm_haichao :),
		(: perform_action, "strike.xiaohun":),
		(: pfm_anran :),
	}));

	create_family("��Ĺ��",3,"������");

	set_temp("apply/damage", 70);
	set_temp("apply/dodge", 60);
	set_temp("apply/attack", 60);
	set_temp("apply/armor", 70);

	if (random(3))
		set("env/��������", "��ӿ");
        set("inquiry", ([
		"��Ĺ" : "���ջ�ɽ����Ӣ�۾��������������ڴ��������꣬�������£�����\n"+
			"�����ڴ˳���һ�����������ӣ�",
		"С��Ů" : "�������Ұ��ޣ�������������",
		////"������" : (: ask_sword :),
		//"��������" : (: ask_sword :),
       /// "�书"  : (: ask_skill :),
		//"����"  : (: ask_guojing :),
		//"����"  : (: ask_huangrong :),
		//"��ܽ"  : (: ask_guofu :),
		//"��Ů��"  : (: ask_shunv :),
		"��Ȼ������"  : (: ask_anranzhang :),
		"ʷ���ֵ�����"  : (: ask_liaoshang :),
		"����"  : (: ask_yinggu :),
		"�ܲ�ͨ"  : (: ask_zhou :),
		//"�ɸ�"  : (: ask_mengge :),
		////"����"  : (: ask_skill1 :),
		////"�ڹ�"  : (: ask_skill2 :),

	]));

    setup();
	carry_object(BINGQI_D("sword/gangjian"));
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object("/d/gumu/obj/pao1")->wear();
}

void init()
{
	object ob = this_player();
	if (ob->query("quest/anran/pass"))
	{
	   add_action("do_learn","learn");
	   add_action("do_learn","xue");
	}
	::init();
}


//��Ȼ�ƿ�ʼ

int ask_anranzhang()
{
	object me=this_player();
	
	if (me->is_busy()) return 0;
	if (this_object()->is_busy())
	{
		command("say û���Һ�æô����һ�������ʣ�\n");
		return 1;

	}
	if (!me->query("quest/shendiao/��ѩ�����/healover"))
	{
		
		command("say �������Դ���һ���Ʒ�������һʮ���С������Դ��������ھ���ȱƲ����ѷ��ֺ󣬱㴳��������\n");
		command("say �����ĺ����������壬�Ӷ��书�ճ�������֮�󣬳����ڹ�ѭ�򽥽��⣬����޿�����������˼��С��Ů��\n");
		command("say ��������������һ���ں����������ã���������֮������ȭ����ߣ�����һ�Ʊ㽫��ʯ��÷��顣���ɴ���˼��\n");
		command("say ����һ���������Ʒ���������Ѱ���书���죬����֮����ȫ���������Ҿͽ������Ʒ�����Ϊ����Ȼ�����ơ���\n");
		command("say ȡ���ǽ��ͱ�����һ�䡰��Ȼ�����ߣ�Ψ������ӡ�֮�⡣");
		if (me->query_skill("force",1)<500)
		{
			command("say �����书ȫ���ۻ������������������ڹ�̫��������500��ѧ��Ҳ�Ƕ��ҵ��ˡ�\n");
			return 1;
		}
		if (me->query("max_neili")<20000)
		{
			command("say �����书ȫ���ۻ�������������������������20000��ѧ��Ҳ�Ƕ��ҵ��ˡ�\n");
			return 1;
		}
		command("say ������ѧ���ž�������������ȥ�켸���£����յõ���Ϣ��˵�������ϵ�ʷ���ֵ����ѡ�\n");
		command("say ʷ���ֵ�һ����ҹ�ϵ�ܺã������ȥ�������Ķ�����ʲô���ˡ�\n");
		me->set("shendiao/��ѩ�����/askanran",1);
		me->set_temp("quest/shendiao/��ѩ�����/askanran",1);
		return 1;
	}
	if (me->query("quest/anran/pass"))
	{ 
		command("say ��λ"+RANK_D->query_respect(me) +"�����Ѿ�����Ȼ�ƵĿھ��������ˣ����ѵ��ڶ�����ô����");
		return 1;
	}	
	
	if ((time()-me->query("quest/anran/time"))<86400)
	{ 
		command("say ��λ"+RANK_D->query_respect(me) +"��������̫Ƶ���ˣ���");
		return 1;

	}
	if (me->query("gender")!="����")
	{
			command("say ��Ȼ���������Ǵ������书�����������ʲ�����ϰ��\n");
			return 1;
	}
	if(me->query("divorce"))
	{
		command("say ��������飬���ʹ�á���Ȼ����֮�⡹��\n");
        return 1;
		
	}	
	command("haha "+me->query("id"));
	command("say С�ֵ��������壬���ǲ�����Ȼ���������书�����Ե���Ǿ������ˡ�\n");
	me->start_busy(999);
	this_object()->start_busy(30);
    //remove_call_out("anran_think");
	call_out("anran_think",1,me);
	return 1;
}
// ���� ����

int ask_liaoshang()
{
	object me=this_player();
	if (!me->query_temp("quest/shendiao/��ѩ�����/askyingfox"))
	{
		return notify_fail("���Ҵ���ʲô��\n");
	}
	command("say ʷ���ֵܵ�����ԭ������Ҫ�����Ѫ��ҩ���ӡ�\n");
	command("say ���µ�ȷ��Щ�Ѱ졣\n");
	me->set_temp("quest/shendiao/��ѩ�����/askyangshang",1);
	return 1;
	
}
int ask_yinggu()
{
	object me=this_player();

	if (!me->query_temp("quest/shendiao/��ѩ�����/askyangshang"))
	{
		return notify_fail("�������Ƕλ�ү�Ĺ��������Ҵ���ʲô��\n");
	}
	command("say ԭ������ô���£�\n");
	command("say ��Ȼ��������Ķ���,˵�����Ѿ��ҵ�����ˡ�\n");
	command("say ֻ��������ͯ���������ԩ��ȷʵ��Щ�������԰���\n");
	command("think");
	command("consider");
	me->set_temp("quest/shendiao/��ѩ�����/askyangying",1);
	return 1;
}
int ask_zhou()
{
	object me=this_player();

	if (!me->query_temp("quest/shendiao/��ѩ�����/askyangying"))
	{
		return notify_fail("�ܲ�ͨ������������ʦ�ܣ����Ҵ���ʲô��\n");
	}
	command("say ������ͯ�书��Ϊ�˵ã�������һ���˲������Ķ��֡�\n");
	command("say Ҳ�գ�ֻ���Һ���ȥһ�˰ٻ��ȣ���������ͯ��Ӧ���·��ɡ�\n");
	command("say ����ȥȫ��̸����İٻ���ȥ��������ͯ�������͵���\n");
	me->set_temp("quest/shendiao/��ѩ�����/askyangzhou",1);
	return 1;
}

void attempt_apprentice(object ob)
{
	mapping fam = ob->query("family");
	if(!fam || fam["family_name"] != "��Ĺ��"){
		command("say "+RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}
	if(ob->query("gender") != "����") {
		command("bow "+ ob->query("id"));
		command("say �ҿ�ֻ����ͽ����ȥ�������������԰ɡ�");
		return;
	} 
	if(ob->query("divorce"))
	{
		command("��������飬��ζ��á���Ů�ľ����ľ��裡\n");
        return;
	}	
	if((int)ob->query_skill("yunu-xinjing", 1) < 350) {
		command("say ��Ů�ľ��ڹ��ǹ�Ĺ�书֮������"); 
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ�������ڹ��϶��µ㹦��350����");
		return;
	}   
	if((int)ob->query_int() < 50 ) {
		command("say �ҵ��书��Ҫ���ߵ����Բ���ѧ�ᣨ50����");
		command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
		command("say "+RANK_D->query_respect(ob)+"�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	if((int)ob->query("shen") < 2000000){
		command("say �ҹ�Ĺ�������߽����У�һ���������塣");
		command("say ��λ" + RANK_D->query_respect(ob)+"��������2m��ȥ������������º������ɣ�");
		return;
	}
	command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");         
    command("chat ��Ĺ�书���ֽ�����"+ ob->name() +"�ɱ���Ϊʦ�������ˣ�");
    command("chat* pat " + ob->query("id"));
	command("recruit " + ob->query("id"));
	ob->set("title","��Ĺ��������´���");
}

//��������ʼ

string ask_guojing()
{
	object me=this_player();
	command("say ���������Ҹ��׵����֣����Һܺã����͹���ĸһ���ྴ�����\n");
	command("say �Ҵ�С�������չ˺ͽ̵������������������ӡ�\n");
	command("say ��������һЩ���飬ʹ������Ϊ�����Ҹ��׵������ǹ�����\n");
	command("say �Ҳ��Ϊ�˷��´��\n");
	command("sigh ");
	command("consider ");
	command("say ����ĸ���Ҳ�û���������Һá�\n");
	me->set_temp("xtjf/askguo",1);
	return "��ʵ��Сʱ���Ҿ�֪������Ϊ�˲��ù��������ģ���һֱû˵������\n";
}
string ask_huangrong()
{
	object me=this_player();
	if (!me->query_temp("xtjf/askguo"))
		return "���������ʲô���ѵ���ʲô������ͼ���ɣ�\n";
	me->delete_temp("xtjf/askguo");
	command("say ����ĸ�ǹ����������ӣ����͹�����һ���ྴ�����\n");
	command("say �Ҵ�С�������չ˺ͽ̵������������������ӡ�\n");
	command("say ��ȻСʱ�����ĸ���Ҳ���̫�ã�������Щ�����ң������붼�������᲻���µ��µġ�\n");
	command("say ��������֪���ҵ�������ʱ���Ҳ����ף���ԭ���������Ҹ��ף�\n");
	command("sigh ");
	command("consider ");
	command("say �����и�Ů���й�ܽ��Сʱ������һ�����һ�����ˣ,������ܣ�������\n");
	command("laugh ");
	command("say ��������������һ�������¼����Ӷ�ʹ���ҵ�����������������ת,��ȫ���ݹ�ܽ���ͣ�\n");
	
	me->set_temp("xtjf/askhuang",1);
	return "������һֱ�Դ������ͻ����Ų��£�����ԩ������\n";
}
string ask_guofu()
{
	object me=this_player();
	if (!me->query_temp("xtjf/askhuang"))
		return "���������ʲô���ѵ���ʲô������ͼ���ɣ�\n";
	me->delete_temp("xtjf/askhuang");
	command("say ܽ���ǹ������͹���ĸ��Ů����\n");
	command("say �����ú�Ư�������Ҳ���ϲ��������Ҫ��Ϊ����С�������������Եĺܡ�\n");
	command("say ������������������Ȼһ�����ҵ���۸��ϵ��������Ҳ���Ϊ���ˡ�\n");
	command("say �ҵ�ʱ�����ڵأ��Ѻ��ڰ��ΰ���֮�����Ժ��������뵽һ���˼�����֮����\n");
	command("say �ڵ��ֵİ����£��Ҳ����������ˣ�ԭ������Ϊ�Լ��Ӵ˽���Ϊ���ˡ�\n");
	command("say ��֪�����첻���ң��ڵ��ֵİ������Ҿ�Ȼϰ���˽�ħ����ǰ��������������\n ");
	command("say �Ӵ���������һ����ȫ��ͬ������֮·�����Ž����ͽ�������������\n");
	
	command("say ��������������һ�������¼����Ӷ�ʹ���ҵ�����������������ת,��ȫ���ݹ�ܽ���ͣ�\n");
	
	me->set_temp("xtjf/askfu",1);
	return "��ѽ�����Ů�����������Ҿ����������\n";
}
string ask_shunv()
{
	object me=this_player();
	if (!me->query_temp("xtjf/askfu"))
		
		return "���������ʲô���ѵ���ʲô������ͼ���ɣ�\n";
	me->delete_temp("xtjf/askfu");
	command("say ��Ů������������������࣬Ѱ���ط�������Ѱ�ҵ����Ҽǵ����ھ�����С�\n");
	command("say ��Ů�����Ƕ���һ��֮�����˼����ʤ���ꡣ\n");

	me->set_temp("xtjf/askshunv",1);
	return "�������ľ�������ȥ����������\n";
}

//Ѱ����Ů��
int accept_object(object me, object obj,object ob)
{
	ob = this_object();
	if (!me->query_temp("xtjf/askshunv")) return 0;
	
	if (obj->query("id")=="shunu jian")
	//&& obj->query("name")=="��Ů��"
	{
		message_vision(HIC"$N�������Ů���������У�������ȥ�Ĺۿ���������ɫ��ò�����\n"NOR,ob);
		command("say ��ѽ����Ǵ���֮���ô�����ˣ���Ȼ������˵ķ�����\n");
		command("say �ţ���Ȼ����ô���ģ��Ҿ�������С�����ˡ�\n");
		message_vision(HIC"$N�������Ů�����뽣�ʣ�˳���ӵ�һ�ԣ�������ᣬ�������̬������������ת��\n"NOR,ob);
		command("sigh ");
		command("say ���Ȼ���ľ����Ұ�ڶ����°ɣ�ȥ������������ɸ����ɱ�ˣ�Ҳ�����Ұ��������һ��æ�ˡ�\n");
		//me->delete_temp("xtjf/askshunv");
		me->set_temp("xtjf/shunvok",1);
		destruct(obj);
		return 1;

	}
	if (obj->query("id")=="shouji" &&obj->query("name")=="�ɸ���׼�" )
	{
		if (!me->query_temp("xtjf/shunvok"))
		{
			command( "say �����ҽ�����ĵ�һ�����鶼�첻�ã�������������\n");
			return 1;
		}
		message_vision("$N��һ���ɸ���׼��ݸ�$n�ۿ���\n",me,ob);
		command("laugh ");
		command("say �ã���λ��ʿ���ǲ��������������ն�Ͻ��׼�������Ӣ��Ҳ��\n");
		command("say ��Ȼ������г��⣬��ô������ȥ���ҵ�һλ����˸���ɱ�ˡ�\n");
		command("say �����ɹŹ���һ��ʦ�����ַ��������������������Ǵ�ɾ��磬��Ҫ���ġ�\n");
		command("say ��ʵ�ڴ򲻹�Ҳ���ó�ǿ�����������Ҫ�������֣�\n");
		me->delete_temp("xtjf/shunvok");
		me->set_temp("xtjf/killmg",1);
		return 1;
	}
	if (obj->query("id")=="shouji"&& obj->query("name")=="���ַ������׼�")
	{
		if (!me->query_temp("xtjf/killmg"))
		{
			command( "�����ҽ�����ĵڶ������鶼�첻�ã�������������\n");
			return 1;
		}
		message_vision("$N��һ�Ž��ַ������׼��ݸ�$n�ۿ���\n",me,ob);
		command("laugh ");
		command("say �ã���λ��ʿ���ǲ�����Ȼ�ܽ����ַ����������ɱ����\n");
		command("say �ţ����Ĳ����ǵ��ļ����������Ұ���ö���Ͻ���ľ��鵤��������\n");
		command("say ��ö���鵤���������������������黨���ġ�\n");
		me->delete_temp("xtjf/killmg");
		
		me->set_temp("xtjf/killfawang",1);
		return 1;
	}
	//&& obj->query("name")=="���鵤"
	if ( obj->query("id")=="jueqing dan" )
	{
		if (!me->query_temp("xtjf/killfawang"))
		{
			command( "�����ҽ�����ĵ��������鶼�첻�ã�������������\n");
			return 1;
		}
		message_vision("$N��һ�ž��鵤�ݸ������\n",me);
		command("laugh ");
		command("say �ã�������ö���鵤���������黨֮���ؽ����ˣ�\n");
		command("say ��Ȼ��ˣ���������ҽ��Ǳ�����������������\n");
		command("say �Ҹ����������ķ��ţ��ܷ�����Ϳ�����˵������ˡ�\n");
		command("say ��һ��Ҫȥ��ڣ�Ķ���������ȥ��أ���ȥ���ˣ�˵�����ᱻ�������ˣ�\n");
		me->delete_temp("xtjf/killfawang");
		me->set_temp("xtjf/getjqd",1);
		return 1;
	}
//&&obj->query("name")=="������"
	if (obj->query("id")=="xuantie jian")
	{
		if (!me->query_temp("xtjf/getjqd"))
		{
			command( "�����ҽ�����ĵ��ļ����鶼�첻�ã�������������\n");
			return 1;
		}
		message_vision(HIY"$N������������������У�������ȥ�Ĺۿ�����������ĸ�������������������ᡣ\n"NOR,ob);
		command("say �ؽ��޷棬���ɲ�����\n");
		command("say �����������еĵ�����ô����\n");
		message_vision(HIM"$N����������ؽ����������ߣ��������ᣬ�����Ƕ�������ĮȻ,�·�����ʲô��\n"NOR,ob);
		command("sigh ");
		command("say ���Ȼ���ľ����Ұ�ڵ�����°ɣ�������Ϊ����ֻ�ð����������İ��ظ������ˡ�\n�ܷ�����Ϳ����Լ��������ˣ��������������ǿ����������Ժ���Ҫ��\n");
		me->delete_temp("xtjf/getjqd");
		me->set_temp("xtjf/getxtjok",1);

		me->set("xtjf/getxtjok",1);
		obj->destruct();
		return 1;
	}

    return 1;
	
}

string ask_sword()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	if (this_object()->is_busy())
	{
		return RANK_D->query_respect(ob) +"û���Һ�æô����һ�������ʣ�\n";

	}
	if (!ob->query("xtjf/getxtjok"))
	{
		return RANK_D->query_respect(ob) +"���ҽ���������������ã�����ѧ����������\n";
	}	

	if ( ob->query("shen") < 0)
		return RANK_D->query_respect(ob) +"а��̫�أ���ض���ǰ��Ҳ��Ը���Ľ�������������";

	
	if ( ob->query("max_neili")<15000)
		return "�㵱ǰ�������������15000��ȥ��Ҳ���ղ����ǰ����������㻹�ǰ������������ȥ�ɣ�";
	if ( ob->query_skill("force",1)<450)
		return "�㵱ǰ�Ļ����ڹ���Ϊ����450�����ⲻ�����ٲ���������������������ȥ�ɣ�";
	//���ε�Ů��
	if ( ob->query("gender") == "Ů��"){
		return "��λ"+RANK_D->query_respect(ob) +"������������Ҫ����֮������һ��Ů���ӻ��Ǳ����ɼ������ˡ�";
	}
	if ( ob->query("gender") == "����"){
		return "��λ"+RANK_D->query_respect(ob) +"������������Ҫ����֮���������������������ɵġ�";
	}
	//��ӽ��ܻ���
	if (ob->query("quest/xtj/pass"))
	{ 
		return "��λ"+RANK_D->query_respect(ob) +"�����Ѿ��ѿھ��������ˣ����ѵ��ڶ�����ô����";
	}	
	if (time()-ob->query("quest/xtj/time")<86400)
	{ 
		return "��λ"+RANK_D->query_respect(ob) +"��������̫Ƶ���ˣ���";

	}
	//�ж��Ƿ��������
	//Ѱ����Ů����ɱ�ɸ磬ɱ���ַ�������������	
	this_object()->start_busy(30);

	if ( ob->query("gender")=="����") {
		command("pat "+ ob->query("id"));
		command("say ���������������ϣ����������������ڶ��´���Ĺǰ��������������");
		command("say");
		//ob->set("ygpass", 1);
		ob->start_busy(999);
		remove_call_out("thinking");
		call_out("thinking",1,ob);
		
		return "������Ϣ���������У����ص����ú�����һ�°�,������������ȥ�ٲ��Ķ����ԡ�\n";
	}	
	
}

int pfm_haichao()
{
	object me,weapon;
	me = this_object();
	weapon = present("gangjian",me);
	if( me->is_busy()) return 0;
	if( objectp(weapon)){
		set("jiali", 50);
		command("wield jian");
		command("perform haichao");
		if(random(10) > 5){
			set("jiali", 150);
			command("unwield jian");
		}
		return 1;
	}
	else {
		new(BINGQI_D("sword/gangjian"))->move(me);
		set("jiali", 50);
		command("wield jian");
		command("perform haichao");
		if(random(10) > 5){
			set("jiali", 150);
			command("unwield jian");
		}
		return 1;
	}
	return 1;
}

int pfm_anran()
{
	object me,weapon;
	me = this_object();
	weapon = me->query_temp("weapon");

	if(me->is_busy()) return 0;
	if( me->query("eff_qi") < 1 ) return 0;
	if( me->query("max_qi") / me->query("eff_qi") < 2 ) return 0;
	if(objectp(weapon)) weapon->unequip();
	this_object()->set("jiali", 150);
	command("perform anran");
	return 1;
}

string ask_skill()
{
	mapping fam;

	if( !(fam = this_player()->query("family")) || fam["family_name"] != "��Ĺ��" )
		return "����"+RANK_D->query_respect(this_player())+"���޹ϸ𣬲�֪�˻��Ӻ�̸��";

	if( this_player()->query_temp("gumu_skill") )
		return RANK_D->query_respect(this_player()) + "�������������̡����������ڹ�����������⣡";

	if( this_player()->query_skill("sword") < 150 )
		return RANK_D->query_respect(this_player()) + "�Ľ����ƺ���������������";

	if( this_player()->query("gumu_given") >= 300 )
		return RANK_D->query_respect(this_player()) + "������书�Ѿ������ˣ����Ѿ�ûʲô����ָ�̵��ˡ�";

	if( this_player()->query_skill("yunu-xinjing", 1) > this_player()->query("gumu_given") + 30 ) {
		this_player()->set_temp("gumu_skill", 1);
		return RANK_D->query_respect(this_player()) + "���ڹ����о������Ҿ�ָ���㼸�°ɣ����������ҹ��ڡ�"HIY"����"CYN"����"HIY"�ڹ�"CYN"�������ʣ�";
	} else {
		return "�ҽ��ڲ��Ǹ�ָ�̹�������ѧ�Ĺؼ����Ļ����Լ�Ŭ����ϰ����\n";
	}
}

int prevent_learn(object ob, string skill)
{
	if (skill == "anran-zhang")
		return 0;
	return 1;
}

int is_apprentice_of(object ob)
{
	return 1;
}
 
int recognize_apprentice(object ob)
{
	return 1;
}


//����ķ��
/*
string ask_skill1()
{
	object me, ob;
	int skill, pot;
	mapping fam;

	me = this_player();
	ob = this_object();

	if( !(fam = this_player()->query("family")) || fam["family_name"] != "��Ĺ��" )
		return "����"+RANK_D->query_respect(this_player())+"���޹ϸ𣬲�֪�˻��Ӻ�̸��";

	if( this_player()->query_skill("sword") < 150 )
		return RANK_D->query_respect(this_player()) + "�Ľ����ƺ���������������";

	if( !me->query_temp("gumu_skill") )
		return "���������������ϣ����������������ڶ��´���Ĺǰ��������������";

	if( (int)me->query_skill("yunu-xinjing", 1) > 300 ) 
		skill = 300 - (int)me->query("gumu_given");
	else skill = (int)me->query_skill("yunu-xinjing", 1) - (int)me->query("gumu_given");

	pot = skill * 10;
	pot += random(pot/2);

	skill /= 30;
	if( skill < 1 ) skill = 1;

	message_vision(HIB"$n΢Ц��������еĽ�������죬������ᣬ����Ȼ�����������֮�������������š�\n"NOR,me,ob);
	message_vision(HIW"$N����$n��չʾ�ķ�����ϰ����Ȼ�书���г�����\n"NOR,me,ob);

	me->delete_temp("gumu_skill");
	me->set("gumu_given", (int)me->query_skill("yunu-xinjing", 1));

	me->set_skill("xuantie-jianfa", me->query_skill("xuantie-jianfa", 1) + skill );
	me->set_skill("quanzhen-jianfa", me->query_skill("quanzhen-jianfa", 1) + skill );
	me->set_skill("yunu-jianfa", me->query_skill("yunu-jianfa", 1) + skill );
	me->set_skill("sword", me->query_skill("sword", 1) + skill );
	me->add("potential", pot );

	tell_object(me, HIC"��ġ����������������ˣ�\n"NOR);
	tell_object(me, HIC"��ġ�ȫ�潣���������ˣ�\n"NOR);
	tell_object(me, HIC"��ġ���Ů���Ľ��������ˣ�\n"NOR);
	tell_object(me, WHT"���������" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR);

	return RANK_D->query_respect(me) + "���ʹ��ˣ����Ǹ�����֮�Ű�����������";
}

string ask_skill2()
{
	mapping fam;
	object me, ob;
	int skill, neili;

	me = this_player();
	ob = this_object();

	if( !(fam = this_player()->query("family")) || fam["family_name"] != "��Ĺ��" )
		return "����"+RANK_D->query_respect(this_player())+"���޹ϸ𣬲�֪�˻��Ӻ�̸��";

	if( this_player()->query_skill("sword") < 150 )
		return RANK_D->query_respect(this_player()) + "�Ľ����ƺ���������������";

	if( !me->query_temp("gumu_skill") )
		return "������Ϣ���������У����ص��������ں�ˮ�������ľ��ϣ���ú�ȥ����һ�°ɡ�";

	if( (int)me->query_skill("yunu-xinjing", 1) > 300 ) 
		skill = 300 - (int)me->query("gumu_given");
	else skill = (int)me->query_skill("yunu-xinjing", 1) - (int)me->query("gumu_given");

	neili = skill/2;
	neili += random(neili/4);

	skill = random(skill)/30;
	if( skill < 1 ) skill = 1;

	message_vision(HBYEL"$n������Ϣ���������У����ص�����������ۼ�������������Ů�ľ���\n"NOR,me,ob);
	message_vision(HIW"$N����$n�������������Ŷ�ʱ�⿪�����ڹ��������ָ�����һ�㡣\n"NOR,me,ob);

	me->delete_temp("gumu_skill");
	me->set("gumu_given", (int)me->query_skill("yunu-xinjing", 1));

	me->set_skill("yunu-xinjing", me->query_skill("yunu-xinjing", 1) + skill );
	me->set_skill("force", me->query_skill("force", 1) + skill );
	tell_object(me, HIC"��ġ���Ů�ľ��������ˣ�\n"NOR);
	tell_object(me, HIC"��ġ������ڹ��������ˣ�\n"NOR);

	me->add("max_neili", neili );
	tell_object(me, WHT"���������Ϊ������" + chinese_number(neili) + "�㡣\n"NOR);

	return RANK_D->query_respect(me) + "���ʹ��ˣ����Ǹ�����֮�Ű�����������";
}
*/

