// hezudao.c (kunlun)

inherit NPC;
#include <ansi.h>
string ask_qin();
string ask_xunlei();
string ask_qinjian();
string ask_book4();
string ask_liangyi();
string ask_zfliangyi();
string ask_hundun();
string ask_diezhang();

void create()
{
	object ob;
	set_name("�����", ({ "he zudao", "he" }));
	set("title", "�����ɿ�ɽ��ʦ");
	set("nickname", HIW"������ʥ"NOR);
	set("long",
		"�����������ɿ�ɽ��ʦ���ų��ٽ��������ġ�������ʥ����\n"
		"������Ŀ���ݹ����⣬ԼĪ��ʮ��������͡�\n");
	set("gender", "����");
	set("age", 35);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("per", 27);
	set("str", 35);
	set("int", 40);
	set("con", 30);
	set("dex", 28);

	set("max_qi", 35000);
	set("max_jing", 8500);
	set("neili", 38000);
	set("eff_jingli", 7000);
	set("max_neili", 38000);
	set("jiali", 250);
	set("combat_exp", 15500000);
	set("unique", 1);
	set("score", 40000);
	set("quest/kl/xtwj/qinjian/pass",1);
	set("quest/kl/lyj/xunlei/pass",1);
	set("quest/kl/lyj/hundun/pass",1);
	set("quest/kl/lyj/liangyi/pass",1);

	set("qinji-book",1);
	set("chat_chance_combat", 85);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.feihua" :),
		(: perform_action, "sword.jinzhen" :),

  		(: perform_action, "sword.hundun" :),
		(: perform_action, "sword.xunlei" :),
  		(: perform_action, "sword.liangyi" :),
		(: exert_function, "wuji" :),			
		(: exert_function, "qinjian" :),
  		(: perform_action, "sword.feipu" :),
	}));

	set("inquiry", ([
		"��" : (: ask_qin :),
		"Ѹ�׽���" : (: ask_xunlei :),
		"�ٽ�˫������" : (: ask_qinjian :),
		"��β��" : (: ask_qin :),
		"�ټ��߼�ƪ" : (: ask_book4 :),
		"�����Ǿ�" : (: ask_liangyi :),
		"�������Ǿ�" : (: ask_zfliangyi :),
		"���罣��" : (: ask_hundun :),
		//"�����������" : (: ask_xu :),
		"�����Ƶ���" : (: ask_diezhang :),

	]));

	set_skill("art", 200);
	set_skill("literate", 200);

	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	//set_skill("xunlei-jian", 500);
	set_skill("strike", 500);
	set_skill("kunlun-zhang", 500);
	set_skill("parry", 500);
	set_skill("sword", 520);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("liangyi-jue", 220);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);
	set_skill("liangyi-jian", 520);


	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("strike", "kunlun-zhang");
	map_skill("cuff", "zhentian-quan");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	prepare_skill("strike", "kunlun-zhang");

	add_temp("apply/sword", 150);
	add_temp("apply/parry", 100);
	add_temp("apply/force", 100);
	add_temp("apply/dodge", 100);
	add_temp("apply/strike", 100);
	add_temp("apply/damage", 75);

	create_family("������", 1, "��ɽ��ʦ");
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/jwqin"));
		if (!ob) ob = new(BINGQI_D("guzheng"));
		ob->move(this_object());
		ob->wield();
		carry_object("/d/kunlun/obj/pao1")->wear();
	}
}

void attempt_apprentice(object ob)
{
	object letter;
	if(ob->query_int() < 50 ) {
		command("say ����������Ҫ���Լ��ߵ��˲�(50����)�������������У��������书�������ۡ�");
		command("say "+RANK_D->query_respect(ob)+"�����Ȼ�ȥ�������ɡ�");
		return;
	}
	if ((int)ob->query_skill("xuantian-wuji", 1) < 350) {
		command("say �����޼�Ϊ���ɸ�����");
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ�����������޼�����350���϶��µ㹦��");
		return;
	}
	if ((int)ob->query_skill("liangyi-jian", 1) < 350) {
		command("say ���ǽ�Ϊ���ɸ�����");
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���������ǽ���350���϶��µ㹦��");
		return;
	}
	if ((int)ob->query_skill("taxue-wuhen", 1) < 350) {
		command("say ̤ѩ�޺�Ϊ���ɸ�����");
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ������̤ѩ�޺ۣ�350���϶��µ㹦��");
		return;
	}
	if ((int)ob->query_skill("art", 1) < 150) {
		command("say ��������ʥ�����彣���ƣ�������Ҳ���ˡ�");
		command("say " + RANK_D->query_respect(ob)+
			"�Ƿ������黭����Ϊǳ��Щ�أ�200����");
		return;
	}
	if ((int)ob->query("max_neili", 1) < 6000) {
		command("say ����������6000����һ�Ķ����������߻���ħ��");
		command("say " + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ���Ⱥú�����������");
		return;
	}
	if ( ob->query("gender") == "����" && ob->query_skill("zhentian-quan", 1) < 350 ){
		command("say "+ RANK_D->query_respect(ob) +"�Ƿ�Ӧ����������ȭ��350���϶��µ㹦��");
		return;
	}
	if ( ob->query("gender") == "Ů��" && ob->query_skill("chuanyun-tui", 1) < 350 ){
		command("say "+ RANK_D->query_respect(ob) +"�Ƿ�Ӧ�����ڴ������ϣ�350�����µ㹦��");
		return;
	}
	if (!ob->query_temp("kl/baihe/fangxin"))
	{
		command("��Ҫ����Ϊʦ���ã��������һ���ţ���Ҫ�͵������£�����������Ұ��ˣ��Ҿ������㡣\n");
		if (present("bai tie",ob))
		{
			command("say �ߣ����Ѿ�����ȥ����һ�ˣ�����ô������ȥ��");
			return;
		}
		if (ob->query_temp("klbs/askhe"))
		{
			command("say �ߣ����Ѿ�����ȥ����һ�ˣ���Ϊ�����������");
			return;
		}
		letter=new("d/kunlun/obj/baitie");
		letter->move(ob);
		
		ob->set_temp("klbs/askhe",1);
		
		command("say �ðɣ��������һ���ţ���д���������ŵģ����������һ�ˣ������Ӹ����š�\n");
		return;

	}
	command("say ������Ҳ���������ˣ��Ҿͽ���һЩ�ٽ����֪ʶ�ɡ�");
	command("recruit "+ob->query("id"));
	ob->set("appren_hezudao", 1);
	//Ԥ���ж���һ�����ڲ���
	ob->delete_temp("klbs/askhe");
	ob->delete_temp("kl");
	ob->set("title",HIC"������ʥ�״�����"NOR);
}
void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("sword/jwqin")))) {
		ob->move(this_object());
		command("wield jiaowei qin");
	}
}

string ask_qin()
{
	object me = this_player();

	if (me->query("family/master_name") != "�����")
		return "�⽹β�����������ɵı���㲢���ҵĴ��ˣ����ܸ��㣡";

	if (present("jiaowei qin",this_object())) {
		command("unwield jiaowei qin");
		command("give jiaowei qin to " + me->query("id"));
		return "�⽹β�پ͸����ˣ����Ҫ���Ʊ��ܺã�";
	}
	return "�������ˣ���β�����Ѿ����������ˡ�";
}
//�ٽ�quest��ڡ���

string ask_qinjian()
{
	object me = this_player();

	if (me->query("family/master_name") != "�����"
		||me->query("family/master_id") != "he zudao")
		return "���ٽ�˫��������������ʥ�Ĳ���֮�գ��㲢���ҵĴ��ˣ����ܴ��ڸ��㣡";
	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		return "������ɵ��ӣ����ʴ�����������";
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

	
    if( me->query_skill("xuantian-wuji", 1) < 350 )
		return "��������޼����費��350�����޷������������ǽ����ľ�Ҫ���ڣ�";
	
	if( me->query("quest/kl/xtwj/qinjian/pass") )
		return "���Ѿ�������������ܣ��ֺιʿ�����Ц�أ�";

	if ((int)me->query("int")<35)
		return "���ٽ�˫���ܿ����ԣ�����������35���������ң�\n";
	
	
	if( time()- me->query("quest/kl/xtwj/qinjian/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";
	
	command("say ��ʮ��ǰ��������֮�У���������ȥ��һ���ţ���ʱ����һλ�������ֵĸ��֡�\n");
	command("say ���⻹����һλ��Ů����֮˵���й��壬�����ǹ�����ĸ���ǻ��ء�\n");
	command("say ��ʱ�Ҹյ���һ���������ֵߵߵ�������Ʒ����˭֪��������ɽ�µ�ӭ��ͤ�����������֡�\n");
	command("say �Ұ����Ǵ����ˣ��õľ��������޼�����һ�Ķ���֮����\n");
	command("say �������Ȥ������ȥ�Ķ�������˵������ʲô�ջ�\n");
    me->set_temp("qinjian/askhe",1);

	return "���ٽ��������ǿ����ԣ���ͽ���ܷ���������컯�ˣ�";
	

	
}
//ask xunlei ����
string ask_xunlei()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       

	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		return "������ɵ��ӣ����ʴ�����������";

	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

    if( me->query_skill("xuantian-wuji", 1) < 300 )
		return "��������޼����費��300�����޷������������ǽ����ľ�Ҫ���ڣ�";
	
	if( me->query("quest/kl/lyj/xunlei/pass") )
		return "���Ѿ����������Ѹ�׽������ֺιʿ�����Ц�أ�";

	if ((int)me->query("int")<30)
		return "��Ѹ�׽����ܿ����ԣ�����������30���������ң�\n";
	
	
	if( time()- me->query("quest/kl/lyj/xunlei/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ�Ѹ�׽�����������Ѹ�ײ����ڶ�֮���������У��ұ����Ѿ�������һ��Ѹ�׽�����\n"
						"�����ڵ���ʹ�ã������Ȼ������˳̶ȣ��Ҿʹ�������Ѹ�׽��⣬�Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N�������һ��������һ�мȳ����������಻����������磬Ѹ���ޱȡ�����$n�ۻ�����\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	x=random(me->query("int"));
	command("say ����Ѹ�׾������Ķ������磬Ѹ���ޱȣ������Ž����ľ�Ҫ���ڡ�\n");
	command("pat "+me->query("id"));
	if( i<4
		&& me->query("kar")<31
	//	&& x >= 32
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n�����˺����������ָ�㣬�����������Լ�����Ѹ�׽��������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㽣�����������糤����ӣ����ϲ�����һ���ֽ��м�Ϊ������ʽ������ʶ�ĳ��С�\n"
			             +"��ʽ���Ʒ��������������ʽ���Ѿ���Ȼ���أ��������������಻����\n"
						 +"����������������Ѹ�׾��������÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/lyj/xunlei/pass",1);
		log_file("quest/lyjxunlei", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��Ѹ�׽�������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/xunlei/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ����Ѹ�׽��������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/lyjxunlei", sprintf("%8s(%8s) ����Ѹ�׽�������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/xunlei/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˺������ָ�㣬���Ƕ����ǽ���Ѹ�׽����İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/xunlei/fail",1);
		me->set("quest/kl/lyj/xunlei/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź��������ǽ�֮Ѹ�׽���ʧ��"+me->query("quest/kl/lyj/xunlei/fail")+"�Ρ�\n";
	}


}

string ask_book4()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
		 || fam["generation"] >4
		 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";  
		
		if (this_object()->query("qinji-book")<1)
		{
			 return "�������ˣ������ľ��ѱ���ʦ�������ˡ�";
		}
		this_object()->add("qinji-book",-1);
		ob = unew("/d/kunlun/obj/string-book4.c");     
		ob->move(this_player());

		return "�������б����ټ��߼�����ƪ�������û�ȥ�ú����У��пն�������Ŷ";
}
//����quest
string ask_liangyi()
{
	mapping fam;
	object ob;
	object me=this_player();

	if (!(fam = this_player()->query("family"))
	 || fam["master_name"] != "�����"
	 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";  
	if( me->query_skill("xuantian-wuji", 1) < 350 )
		return "��������޼����費��350�����޷������������ǽ����ľ�Ҫ���ڣ�";
	if( me->query_skill("liangyi-jue", 1) < 200 )
		return "��������Ǿ����費��200�����޷��������������ǽ����ľ�Ҫ���ڣ�";
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}
	if( me->query("quest/kl/lyj/liangyi/pass") )
		return "���Ѿ�������������ǽ������ֺιʿ�����Ц�أ�";
	
	
	if ((int)me->query("int")<30)
		return "�����ǽ����ܿ����ԣ�����������30���������ң�\n";
	
	
	if( time()- me->query("quest/kl/lyj/liangyi/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIC"$N������$n��ͷ��˵���������ɵ����ǽ�������������ǽ�������������������������ϡ�\n"+
						"��������Ҳ�����ݺὭ������Ⱥ����һ���̣����ⲻ��ֻ����һ���������ܺͻ�ɽ�ɵķ����Ǿ���\n"+
						"���ںϣ���ô�����񼼽������ʵı仯��������������Ǹ���Ȥ����ȥһ�˻�ɽ��ɽ��ȥ����\n"+
						"��ɽ������̣��������ɺ��������й����飬����ϰ�÷����ǵİ���������ǽ������״�ɡ�\n"+
				   HIY"\n\n\n$N�·������˳�˼����$n�����о���$N�ƺ����н����ݺᣬ���в��ɵض����Ž�����Ϊ������\n"NOR,this_object(),me);
	me->set_temp("liangyi/askhe",1);
	return "ȥ�ɣ������Ǿ���ϵ�ش�Ҳ���������ĸ�Դ��\n";

}
//�������ǽ������
string ask_zfliangyi()
{
	mapping fam;
	object ob;
	int i,j,k,total;
	object me=this_player();

	if (!(fam = this_player()->query("family"))
	 || fam["master_name"] != "�����"
	 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";  
	if( me->query_skill("xuantian-wuji", 1) < 350 )
		return "��������޼����費��350�����޷������������ǽ����ľ�Ҫ���ڣ�";
	if( me->query_skill("liangyi-jue", 1) < 200 )
		return "��������Ǿ����費��200�����޷��������������ǽ����ľ�Ҫ���ڣ�";
	if( me->query_skill("fanliangyi-jue", 1) < 200 )
		return "��ķ����Ǿ����費��200�����޷��������������ǽ����ľ�Ҫ���ڣ�";
	if (!me->query("quest/kl/lyj/liangyi/jue"))
		return "������߰���������̣�������͵�������ڻ��޷��������������ǽ����ľ�Ҫ���ڣ�";
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

	if( me->query("quest/kl/lyj/liangyi/pass") )
		return "���Ѿ�������������ǽ������ֺιʿ�����Ц�أ�";
	
	if (time()-me->query("quest/kl/lyj/liangyi/time")<86400)
		return "�书̰�಻�ã�������̫�ڿ��ˣ�\n";

	if ((int)me->query("int")<40)
		return "�����ǽ����ܿ����ԣ�����������40���������ң�\n";
	 i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	k=random(me->query("kar"));
	//total=me->query("int")+me->query("str")+me->query("dex")+me->query("con");
	j=random(me->query("int"));
	if (i<3
		&& me->query("kar")<31
		&& j>40
		&& k>27)
	{
	
		command("laugh "+me->query("id"));
		command("chat* pat "+me->query("id"));
		command("chat �ӽ��"+me->query("name")+"������������ʥ���洫���ӣ���������ͬ������ո���");
		command("chat* smile ");
		command("chat �Ҵ����شӴ�����������Ψ�Ҷ���");
		command("say ���˺�����������ǽ��������Ѿ����ڻ��ͨ�ˣ�����������Ŭ����Ϊ�Ҵ�����������ʡ�");
		command("say �����������ǽ����˴�ɣ������Ϊ֮��");
		me->set("quest/kl/lyj/liangyi/pass",1);
		me->set("title",HIG"���ǽ��洫"NOR);
		log_file("quest/zfliangyi", sprintf("%8s(%8s) ʧ��%d�κ�ѧ���������ǳ����ڻ��ͨ�������jȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/liangyi/fail"),j,me->query("kar"),me->query("combat_exp")) );

	}
	else {
		log_file("quest/zfliangyi", sprintf("%8s(%8s) �����������Ǿ�ʧ��%d�Σ��������jȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/liangyi/fail"),j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIG"�����˺������ָ�㣬���Ƕ��������Ǿ��İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		command("angry "+me->query("id"));
		me->add("quest/kl/lyj/liangyi/fail",1);
		me->set("quest/kl/lyj/liangyi/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź������������Ǿ�ʧ��"+me->query("quest/kl/lyj/liangyi/fail")+"�Ρ�\n";
	


	}
	return "������";
}
//���罣������
//���볯¶̨������罣��

string ask_hundun()
{
	mapping fam;
	object ob;
	object me=this_player();
	if (me->query("killer"))
	{
		return "��һ��pker������������\n";
	}
	if (!(fam = this_player()->query("family"))
	 || fam["master_name"] != "�����"
	 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";  
	if( me->query_skill("xuantian-wuji", 1) < 500 )
		return "��������޼����費��500�����޷������������ǽ����ľ�Ҫ���ڣ�";
	if( me->query_skill("liangyi-jian", 1) < 500 )
		return "��������ǽ����費��500�����޷��������������ǽ����ľ�Ҫ���ڣ�";
	if( me->query("quest/kl/lyj/hundun/pass") )
		return "���Ѿ�������������ǽ������ֺιʿ�����Ц�أ�";
	if( time()- me->query("quest/kl/lyj/hundun/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";

	if ((int)me->query("int")<40)
		return "�����ǽ����ܿ����ԣ�����������40���������ң�\n";
	
	command("say ����罣�������ҵ����ڳ�¶̨һ���������Ѱ���ص�����޷��޵á�");
	command("say ��Ȼ�������������Ҿ�ָ����Щ���ϣ�Ȼ����Ҫ�Լ�ȥ����");
	command("say �������Ƿ������򣬾Ϳ���������ˡ�");
	message_vision(YEL"$Nֻ��һ�ɴ����������������Ƽ�������\n"NOR,me);
	me->set_temp("hundun/askhe",1);
	me->move("d/kunlun/zhaolutai");
	return "�����泯�죬ֻ������ǰ�̿���ϴ��Զ���ƾ����棬����������Ԩ��\n";
}

//���ص���

string ask_diezhang()
{
	object me;
	int i,j;
	me=this_player();

	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("kunlun-zhang",1)< 400)
	{
		return "��������Ƶȼ�����500��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/klz/diezhang/pass"))
	{
		return "���������Ѿ��⿪�ˡ���\n";
	}
	if (time()-me->query("quest/kl/klz/diezhang/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ������ƽ����ı����͹�����񣬺��������ɶ���̫��ͬ��\n"
						"���Ȼ������˳̶ȣ��Ҿʹ��������е��Ƶİ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N����Ծ��˫���˹�����������$n�����ҡ��\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say �㿴����ô��\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n�����˵ĺ����ʦ��������ָ�㣬�����������Լ����������Ƶ������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n���������������������Ƶ��Ƶ����÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/klz/diezhang/pass",1);
		log_file("quest/klzdiezhang", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������Ƶ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/diezhang/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ���������Ƶ��ƾ����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/klzdiezhang", sprintf("%8s(%8s) ���������Ƶ��ƾ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/diezhang/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˺����ʦ����ָ�㣬���Ƕ������Ƶ��Ƶİ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/klz/diezhang/fail",1);
		me->set("quest/kl/klz/diezhang/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź����������Ƶ���ʧ��"+me->query("quest/kl/klz/diezhang/fail")+"�Ρ�\n";
	}


}