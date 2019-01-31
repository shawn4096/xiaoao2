// fengxifan.c (kunlun) ¹���ǣ�һ����Ѫ������
// by sohu
// ������ɰ�ƺ�һ����Ѫ����

inherit NPC;
#include <ansi.h>
string ask_wei();
string ask_tiandi();
string ask_chen();
string ask_hongsha();
string ask_wuxue();
void create()
{
	object ob;
	set_name("������", ({ "feng xifan", "feng" }));
	set("title", "�����ɳ���");
	set("nickname", HIR"һ����Ѫ"NOR);
	set("long",
		"�����������ɸ��֣����������ɳ��ϣ��ųơ�һ����Ѫ����\n"
		"ר�Խ��������Ѩ���������������ˡ��������ۡ��ĸ����\n"
		"����֮�˾�����Ѫ����˵���\n��������Ŀ���ݹ����⣬ԼĪ��ʮ��������͡�\n");
	set("gender", "����");
	set("age", 55);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("per", 27);
	set("str", 30);
	set("int", 25);
	set("con", 30);
	set("dex", 28);

	set("max_qi", 35000);
	set("max_jing", 6500);
	set("neili", 28000);
	set("eff_jingli", 7000);
	set("max_neili", 28000);
	set("jiali", 250);
	set("combat_exp", 13500000);
	set("unique", 1);
	set("score", 40000);
//	set("quest/kl/xtwj/qinjian/pass",1);
	set("quest/kl/xlj/wuxue/pass",1);
	set("quest/kl/klz/hongsha/pass",1);

	set("chat_chance_combat", 85);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.podi" :),
  		(: perform_action, "sword.sanqiu" :),
		(: perform_action, "sword.benlei" :),
  		(: perform_action, "sword.dianxue" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));

	set("inquiry", ([
		"ΤС��" : (: ask_wei :),
		"��ػ�" : (: ask_tiandi :),
		"�½���" : (: ask_chen :),
		"һ����Ѫ����" : (: ask_wuxue :),
		"��ɰ�ƾ���" : (: ask_hongsha :),

	]));

	set_skill("art", 200);
	set_skill("literate", 200);

	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	set_skill("xunlei-jian", 520);
	set_skill("strike", 500);
	set_skill("kunlun-zhang", 500);
	set_skill("parry", 500);
	set_skill("sword", 520);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("liangyi-jue", 220);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);


	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("strike", "kunlun-zhang");
	map_skill("cuff", "zhentian-quan");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "xunlei-jian");
	map_skill("sword", "xunlei-jian");
	prepare_skill("strike", "kunlun-zhang");

	add_temp("apply/sword", 150);
	add_temp("apply/parry", 100);
	add_temp("apply/force", 100);
	add_temp("apply/dodge", 100);
	add_temp("apply/strike", 100);
	add_temp("apply/damage", 75);

	create_family("������", 1, "���г���");
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/gangjian"));
		if (!ob) ob = new(BINGQI_D("changjian"));
		ob->move(this_object());
		ob->wield();
		carry_object("/d/kunlun/obj/pao1")->wear();
	}
}
void init()
{
	object me=this_player();
	if (me->query_temp("quest/kl/klz/hongsha/lugive")
		&&me->query_temp("quest/kl/klz/hongsha/kegive")
		&&me->query_temp("quest/kl/klz/hongsha/yingive")
		&&me->query_temp("quest/kl/klz/hongsha/langive")
		&&me->query_temp("hsz/shedu")
		&&me->query_temp("hsz/chanchudu")
		&&me->query_temp("hsz/֩�붾")
		&&me->query_temp("hsz/Ы�Ӷ�"))
	{
		command("laugh "+me->query("id"));
		command("pat "+me->query("id"));
		command("thumb "+me->query("id"));
		command("say ��Ȼ���Ѿ��Ѽ��������ֶ��أ��Ҿ�����������ɰ�Ƶ�������\n");
		message_vision(HIR"$N���������޼���������ӿ����˫������$N�ĺ󱳣������Ĺɶ���˲���ں���һ��\n"NOR,me);
		me->delete_temp("hsz/shedu");
		me->delete_temp("hsz/chanchudu");
		me->delete_temp("hsz/֩�붾");
		me->delete_temp("hsz/Ы�Ӷ�");
		me->set("quest/kl/klz/hongsha/du",1);
		return;
	}
}

void attempt_apprentice(object ob)
{
	object letter;
	if(ob->query_con() < 50 ) {
		command("say �ҵĹ���ȫƾ��տ���ڹ�(50����)�������������С�");
		command("say "+RANK_D->query_respect(ob)+"�����Ȼ�ȥ�������ɡ�");
		return;
	}
	if ((int)ob->query_skill("xuantian-wuji", 1) < 300) {
		command("say �ҵĹ���ȫƾ��տ���ڹ���");
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ�����������޼�����300���϶��µ㹦��");
		return;
	}
	if ((int)ob->query_skill("art", 1) < 150) {
		command("say ��������ʥ�����彣���ƣ�������Ҳ���ˡ�");
		command("say " + RANK_D->query_respect(ob)+
			"�Ƿ������黭����Ϊǳ��Щ�أ�150����");
		return;
	}
	if ((int)ob->query("max_neili", 1) < 4000) {
		command("say ����������4000����һ�Ķ����������߻���ħ��");
		command("say " + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ���Ⱥú�����������");
		return;
	}
	if ( ob->query("gender") == "����" && ob->query_skill("zhentian-quan", 1) < 250 ){
		command("say "+ RANK_D->query_respect(ob) +"�Ƿ�Ӧ����������ȭ��250���϶��µ㹦��");
		return;
	}
	if ( ob->query("gender") == "Ů��" && ob->query_skill("chuanyun-tui", 1) < 250 ){
		command("say "+ RANK_D->query_respect(ob) +"�Ƿ�Ӧ�����ڴ������ϣ�250�����µ㹦��");
		return;
	}
	/*if (ob->query_skill("kunlun-zhang", 1) < 250 ){
		command("say "+ RANK_D->query_respect(ob) +"�Ƿ�Ӧ�������������ϣ�250�����µ㹦��");
		return;
	}*/

	if (!ob->query("quest/kl/baifxf/baohu"))
	{
		if (ob->query("quest/kl/baifxf/time")&&time()-ob->query("quest/kl/baifxf/time")<86400)
		{
			command("say ������̫Ƶ���ˣ�\n");
			return;

		}
		command("say ��Ȼ���д��ģ�������ȥ����С����һ�ˣ�\n");
		command("say ����˵����д����̿Ͷ�֣��ˬ������ͼ���죬��ȥ���ұ�����֣���ӣ�\n");
		command("say ֣������ݽ��ǰ;�������������в�͵����\n");
		command("say ������֪�������̿��������࣬��������������1��ʱ������ս�پ���\n");
		command("say ���֣����������ʧ���Ժ���Ҫ��������ң�\n");
		ob->set_temp("quest/kl/baifxf/start",1);
		return;
	}
	
	command("say ���������������Ļ����ϣ������������һ��ʱ��ɡ�");
	command("recruit "+ob->query("id"));
	ob->set("appren_fengxifan", 1);
	ob->set("title", HIC"�������洫����"NOR);
	return;
}

string ask_wei()
{
	object me = this_player();

	command("say ����ǰ��ΤС��ð�������̵�ʹ�ߣ�������ҡײƭ��\n");
	command("say �������������ԣ�һֱ���ҵ��ң�������˵����������ػᡣ\n");
	me->set_temp("quest/kl/xjl/wuxue/askfeng",1);

	me->start_busy(1);

	return "��Ȼ������ػᣬ���ٸ������к��³�����\n";
}

string ask_tiandi()
{
	object me = this_player();
	if (!me->query_temp("quest/kl/xjl/wuxue/askfeng"))
	{
		command("say û�±���ɧ���ң��������ӷ��úܣ�\n");
	}

	command("say ��ػ�������һ��������֯���ۼ���һ�ｭ����ͽ��\n");
	command("say ��ػ��ǰ����̨��֣�ɹ��ĺ������֯������Ϊ�½��������ơ�\n ");

	command("heng ");

	me->set_temp("quest/kl/xjl/wuxue/asktiandi",1);
	me->add_busy(1);
	return "���治������ƾ�Ҵ����ص�Ѹ�׽���˭���Ҷ��֣�\n";
}

string ask_chen()
{
	object me = this_player();
	if (!me->query_temp("quest/kl/xjl/wuxue/asktiandi"))
	{
		command("say û�±���ɧ���ң��������ӷ��úܣ�\n");
	}
	command("say ��Ȼ��û���������֣���˵�书���µ�һ��\n");
	command("heng ");
	command("say Ӣ�۲�ʶ�½��ϣ�����Ӣ��Ҳ��Ȼ��\n");
	command("say ����һ�գ����Ϲ�Ҫ������һ����Ѫ֮�֣�\n");
	me->set_temp("quest/kl/xjl/wuxue/askchen",1);
	me->add_busy(1);
	return "�ٺ٣�һ����Ѫ������������׽еģ�\n";
}


int accept_object(object who, object obj)
{
	object obb;
	obb=obj->query("kill_by");
	if (obj->query("id")=="shouji" 
		&&obj->query("name")=="����֮���׼�" 
		&& obb->query("id")==who->query("id"))
	{
		command("say �ô��һ��ͷ­����Ϊ��ɱ�˰�ʤ��������֮�⹷����������ȴ�ҵ�һ�����£�\n");
		command("laugh ");
		command("chat �������Ҵ����غ�ɨ���£��γ�����ﲻ�ٹ�˳���ң�\n");
		who->set("quest/kl/xlj/killhu",1);
		destruct(obj);
		return 1;
	}
	
	if (obj->query("id")=="shouji" 
		&&obj->query("name")=="�½��ϵ��׼�" 
		&& obb->query("id")==who->query("id"))
	{
		command("say �ô��һ��ͷ­����Ϊ��ɱ�˳½����⹷����������ȴ�ҵ�һ�����£�\n");
		command("laugh ");
		command("chat �������Ҵ����غ�ɨ��ػ���Ⱥ��ͽ���γ�����ﲻ�ٹ�˳���ң�\n");
		who->set("quest/kl/xlj/killchen",1);
		destruct(obj);
		return 1;
	}
}
//ask ��ɰ��


string ask_hongsha()
{
	object me, ob;
	int i,j;
	
	ob = this_object();
	me = this_player();       

	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		return "������ɵ��ӣ����ʴ�����������";

	if (!me->query("appren_fengxifan"))
		return "������״����ӣ����ʴ�����������";
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

    if( me->query_skill("kunlun-zhang", 1) < 300 )
		return "������������費��300�����޷��������ɺ�ɰ�Ƶľ�Ҫ���ڣ�\n";
	
	if( me->query("quest/kl/klz/hongsha/pass") )
		return "���Ѿ������������ɰ�ƾ������ֺιʿ�����Ц�أ�\n";
	
	if (!me->query("quest/kl/klz/hongsha/du"))
	{
		if (!me->query_temp("hsz/shedu"))
		{
			command("say ��ϰ��ɰ����Ҫ���߶��������ƣ�������ʹ֮�£�������ϰ��\n");
			me->set_temp("quest/kl/klz/hongsha/asklu",1);
			return "������½������������һ��֮Ե���㵽��������һ���������Ƿ���԰�æ��\n";
		}
		if (!me->query_temp("hsz/chanchudu"))
		{
			command("say ��ϰ��ɰ����Ҫ�����֮���������ƣ�������ʹ֮�£�������ϰ��\n");
			me->set_temp("quest/kl/klz/hongsha/askke",1);
			return "����ɽׯ��ׯ��ŷ������������һ��֮Ե���㵽����ɽׯ������һ���������Ƿ���԰�æ��\n";
		}
		if (!me->query_temp("hsz/֩�붾"))
		{
			command("say ��ϰ��ɰ����Ҫ��֩��֮���������ƣ�������ʹ֮�£�������ϰ��\n");
			me->set_temp("quest/kl/klz/hongsha/askyin",1);
			return "���̵�������������һ��֮Ե���㵽����������һ�ˣ��������Ƿ���԰�æ��\n";
		}
		if (!me->query_temp("hsz/Ы�Ӷ�"))
		{
			command("say ��ϰ��ɰ����Ҫ��Ы�Ӷ��������ƣ�������ʹ֮�£�������ϰ��\n");
			me->set_temp("quest/kl/klz/hongsha/asklan",1);
			return "�嶾�̵��������������һ��֮Ե���㵽����������һ�ˣ��������Ƿ���԰�æ��\n";
		}

	}
	if ((int)me->query("str")<30)
		return "���ɰ�����ǿ��������������������30���������ң�\n";
	
	
	if( time()- me->query("quest/kl/klz/hongsha/time")<86400)
		return "�ţ��㲻�Ǹ�����̹��Һ�ɰ�ƾ����İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIR"$N����$n������˵���������ɵĺ�ɰ���������ص��ƾ������������ڶ���Ĺ�����\n"
					"һ��ʩչ�������������к�ɰ�ƶ������������������࣬�Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIC"\n\n\n$N����������˫��֮�У�˫�ƶ�ʱ��ɳ��һƬ��\n"NOR,this_object(),me);
	
 
    i = 20;
    if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
    i=random(i);
	j=random(me->query("kar"));
	command("say ���ź�ɰ�ƽ������Ǿ����ɺ��������ƣ������ߴ�ֱ���͹�Ѩ���������Ʒ��ľ�Ҫ���ڡ�\n");
	command("pat "+me->query("id"));
	if( i<6
		&& me->query("kar")<31
		&& j >= 24 ) 
	{
		tell_object(me,HIY"\n�����˷�����������ָ�㣬�����������Լ����������Ƶ������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㵤�������������ߣ���Ȼ��˳�м����ϣ�������͹�Ѩ,˫�����������ޱȡ�\n"
							"��Ȼ��һ�ɾ����𵴣��糤����ӣ����ϲ�������ʱͻ���͹�Ѩ�������ơ�\n"
						 +"����������������Ѹ��ɰ�ƾ��������÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/klz/hongsha/pass",1);
		log_file("quest/klzhongsha", sprintf("%8s(%8s) ʧ��%d�κ�ѧ����ɰ�ƾ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/hongsha/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		command("haha"+me->query("id"));		
		
		return "��ϲ�������غ�ɰ�ƾ����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/klzhongsha", sprintf("%8s(%8s) ���ܺ�ɰ�ƾ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/hongsha/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˷�������ָ�㣬���Ƕ������ƺ�ɰ�Ƶİ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/klz/hongsha/fail",1);
		me->set("quest/kl/klz/hongsha/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź��������غ�ɰ��ʧ��"+me->query("quest/kl/klz/hongsha/fail")+"�Ρ�\n";
	}


}
//ask һ����Ѫ

string ask_wuxue()
{
	mapping fam;
	object ob;
	int i,j;
	object me=this_player();

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾������������Ҳ�������״����ӣ���֪�˻��Ӻ�̸��\n";  
	
	if (!me->query("appren_fengxifan"))
		return "������״����ӣ����ʴ�����������";
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

	if(me->query_skill("xunlei-jian", 1) < 300 )
		return "���Ѹ�׽����費��300�����޷���������һ����Ѫ�ľ�Ҫ���ڣ�\n";
	if(me->query_skill("force", 1) < 300 )
		return "��Ļ����ڹ����費��300�����޷���������һ����Ѫ�ľ�Ҫ���ڣ�\n";

	if( me->query("quest/kl/xlj/wuxue/pass") )
	{
		me->set("title",HIR"һ��"HIW"��Ѫ"NOR);
		me->set("mytitle/quest/yjwxtitle",HIR"һ��"HIW"��Ѫ"NOR);
		return "���Ѿ����������һ����Ѫ�ľ������ֺιʿ�����Ц�أ�\n";
	}
	
	if (time()-me->query("quest/kl/xlj/wuxue/time")<86400)
		return "�书̰�಻�ã�������̫�ڿ��ˣ�\n";
	
	if ((int)me->query("int")<30)
		return "��һ����Ѫ�ܿ����ԣ����������Բ���30���������ң�\n";
	/*
	if (!me->query_temp("quest/kl/xlj/wuxue/askchen"))
	{
		command("heng "+me->query("id"));
		return "�������룡\n";
	}*/
	if (!me->query("quest/kl/xlj/killhu"))
	{
		command("say ����ǰ�Ҹ���ʤ��������֮��Щ������Թ�������������������������Ҷ������ߣ�\n");
		command("say ���Ȼ����˳��ģ��Ǿ����Ұ��ǰ�ʤ��������֮����ͷ����������\n");
		return "����˵���̰����ɫ����Ȼ�ڴ���軨԰���˻죬��ȥ���ҿ�����ͷ������\n";
	}

	if (!me->query("quest/kl/xlj/killchen"))
	{
		command("say ���Ȼ����˳��ģ��Ǿ����Ұѳ½����ǹ�������ͷ����������\n");
		return "��һ��Ҫ����ɱ����������ҲŽ��㣡\n";
	}
	message_vision(HIM"$N�����������$n��������˵����������һ����Ѫ�������֪��������\n"+
					"����������ҡ��ҡͷ����̾һ��������������һ����Ѫ���ĳƺ�ȫƾΪʦ������ġ�\n"+
					"���Ź���ĺ����ķ��������������������������ںϵ����⣬Ȼ���Խ��������Ѩ��\n"+
					"���������ܽ��Է�ֱ�ӵ�����������������������֮�У�����Ϊ�伫Ϊ���������ߡ�\n"+
				    "����������������κ����������Խ��������貽����ɥ����\n"NOR,this_object(),me);
	message_vision(HIM"$N�����˿�����˵�������Ź���������󣬺���������Ѱ���书��Щ��ͬ��\n"+
					"��֮ʹ�������������Σ��ܶ��˶���ΪΪʦ�ĺ���������ʵ�����Ƕ���δ֪�Ŀ־���ˡ�\n"+
					"��������Ȥ���Ҿʹ������㣬�ܷ�����Ϳ�����컯�ˣ�������....��\n"NOR,this_object(),me);
	message_vision(HIY"\n\n�������ν�����$n��Ȼ�о�$N������ת֮�ʣ��������۶�ʱ���ͣ��̲�ס���\n"+
				    "��������������$N�ľ���ӿ���������Ȼ��˸��һ�µ��������ϵ�һ��ɻ�ͼ���ϡ�\n"+
					"��������$n˵���������ȥ�����Ǹ�ͼ����\n��\n"NOR,this_object(),me);
	message_vision(HIY"\n\n$n����һ���Ǹ��ɻ��꣬��ʱ���ֵ�ľм��\n"+
				    "$n�Ծ�֮�ʣ����к�Ȼ����һ��֮���������ûʲô�仯����������Ȼ��˹��\n"+
					"$N�ȵ������⵱�еİ�����ɿ����������\n"NOR,this_object(),me);

	i = 20;
    if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
    j=random(i);
	
	if (j<3
		&& me->query("kar")<31
		&&random(me->query("kar"))>27)
	{
	
		command("laugh "+me->query("id"));
		command("chat* pat "+me->query("id"));
		command("chat �ӽ��"+me->query("name")+"������һ����Ѫ�������Ĺ��ŵ��ӣ���������ͬ������ո���\n");
		command("chat* smile ");
		command("chat ��һ����Ѫ�������ĵ��ӴӴ��ݺὭ����\n");
		command("say ���˺�������ҵ��Խ���Ѩ�ľ����Ѿ����ڻ��ͨ�ˣ�����������Ŭ����Ϊ�Ҵ�����������ʡ�\n");
		command("say ������Ѹ�׽��ս��������д����ʣ���Ҫ����Ϊ֮��\n");
		me->set("quest/kl/xlj/wuxue/pass",1);
		me->delete_temp("quest/kl/xlj");

	    me->set("title",HIR"һ��"HIW"��Ѫ"NOR);
		me->set("mytitle/quest/yjwxtitle",HIR"һ��"HIW"��Ѫ"NOR);
		log_file("quest/xljwuxue", sprintf("%8s(%8s) ʧ��%d�κ󣬽�Ѹ�׽�һ����Ѫ���������ڻ��ͨ�������jȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/xlj/wuxue/fail"),j,me->query("kar"),me->query("combat_exp")) );

	}
	else {
		log_file("quest/xljwuxue", sprintf("%8s(%8s) ����Ѹ�׽�һ����Ѫ����ʧ��%d�Σ��������jȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/xlj/wuxue/fail"),j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIG"�����˷�������ָ�㣬���Ƕ�Ѹ�׽�һ����Ѫ�����İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		command("angry "+me->query("id"));
		me->add("quest/kl/xlj/wuxue/fail",1);
		me->set("quest/kl/xlj/wuxue/time",time());
		me->delete_temp("quest/kl/xlj");
		me->start_busy(1+random(3));		
		return "�ǳ��ź�����Ѹ�׽�һ����Ѫ����ʧ��"+me->query("quest/kl/xlj/wuxue/fail")+"�Ρ�\n";
	
	}
	return "������";
}
