// xln.c С��Ů
// By River@SJ 99.05
// ���� ��������Quest By River@SJ 9.25.2001

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_suo(); 
string ask_zhen();
string ask_shoutao();
string ask_yueyin();
string ask_qufengshu();
string ask_ynjfjj();
int pfm_yufeng();
int pfm_hebi();
int ask_hubo();

void create()
{
	object ob;
	set_name("С��Ů", ({ "xiao longnv", "xiao", "longnv" }));
	set("title",HIW"��Ĺ����"NOR);
	set("nickname",HIC"�������"NOR);
	set("long","ӯӯ��վ��һλ�������׵�Ů�ӣ�����������һ��Ѫɫ���Եò԰��쳣��\n"+
		"����һϮ��ɴ��İ��£����������������\n");
	set("gender", "Ů��");
	set("age", 39);
	set("attitude", "friendly");
	set("no_bark",1);

	set("per", 48);
	set("str", 24);
	set("dex", 40);
	set("con", 25);
	set("int", 40);

	set("gmsanwu", 1);
	set("yueyin", 1);
	set("double_attack", 1);
	set_temp("double_attack", 1);
	set("shen", 10000);

	set("combat_exp", 12000000);
	set("max_qi", 29500);
	set("max_jing", 7600);
	set("eff_jingli", 6000);
	set("max_neili", 26000);
	set("neili", 26000);
	set("jiali", 200);
	set("unique", 1);

	set_skill("parry", 500);
    set_skill("hand", 500);
	set_skill("tianluo-diwang", 500);
	set_skill("force", 500);
	set_skill("dodge", 550);
	set_skill("sword", 500);
	set_skill("throwing", 500);
	set_skill("whip", 500);
	set_skill("meinu-quanfa", 500);
	set_skill("cuff", 500);
	set_skill("yunu-shenfa", 550);
	set_skill("yinsuo-jinling", 500);
	set_skill("yunu-jianfa", 500);
	set_skill("quanzhen-jianfa", 500);
	set_skill("yunu-xinjing", 500);
	set_skill("literate", 300);

	map_skill("force", "yunu-xinjing");
    map_skill("hand", "tianluo-diwang");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	map_skill("whip", "yinsuo-jinling");
	map_skill("parry","yinsuo-jinling");
	prepare_skill("cuff", "meinu-quanfa");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "xinjing" :),
		(: perform_action, "whip.yueyin" :),
		(: perform_action, "whip.sanwu" :),
		(: perform_action, "whip.dian" :),
		(: perform_action, "whip.duoci" :),
		(: pfm_yufeng :),
	}));

	create_family("��Ĺ��", 3, "Ů����");

	set("inquiry", ([
		"���" : "�������ҷ������֪�����ܰ��ң���һֱ���������������ơ�",
		"Կ��" : "��....���ҿɼǲ�����������Ƿ��ڹ�Ĺ�����˰ɡ�",
		"������" : (: ask_suo :),
		"�����" : (: ask_zhen :),
		"����" : (: ask_shoutao :),
		"�׽�����" : (: ask_shoutao :),
		"����" : (: ask_yueyin :),
		"��������" : (: ask_yueyin :),
		"������" : (: ask_qufengshu :),
		"�ܲ�ͨ" : (: ask_hubo :),
		"˫�ֻ�������" : (: ask_ynjfjj :),
			
	]));

	set_temp("apply/damage", 80);
	set_temp("apply/dodge", 100);
	set_temp("apply/attack", 100);
	set_temp("apply/armor", 80);
        
	setup();
	if (clonep()){
		ob = unew("/d/gumu/obj/shoutao");
		if (ob) {
			ob->move(this_object());
			ob->wear();        
		}
	}
	carry_object(BINGQI_D("changbian"))->wield();
	carry_object(BINGQI_D("changjian"));
	carry_object("/d/gumu/obj/yfzhen");
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object("/d/gumu/obj/qun1")->wear(); 
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew("/d/gumu/obj/shoutao"))) {
		ob->move(this_object());
		command("wear baijin shoutao");
	}
}

void attempt_apprentice(object ob)
{
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "��Ĺ��"){
		command("say "+RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}
	if( ob->query("gender") != "Ů��") {
		command("wanfu " + ob->query("id"));
		command("say �ҿ�ֻ��Ůͽ����ȥ���ҷ�����԰ɡ�");

		return;
	}
	if (!ob->query("quest/gm/dichuan"))
	{
		command("say �㲢���ҹ�Ĺ�մ����ӣ�������������");
		return;
	}
	if((int)ob->query_skill("yunu-xinjing", 1) < 350) {
		command("say �ҹ�Ĺ�书�ڹ��ǻ���,��Ů�ľ�����350�����������ҡ�"); 
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ�������ڹ��϶��µ㹦��");
		return;
	}
	if((int)ob->query_skill("sword", 1) < 350) {
		command("say �㽣����ô��ҽ̵��㲻һ��ѧ�ûᡣ"); 
		command("say "+RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڽ�����350���϶��µ㹦��");
		return;
	}
	if((int)ob->query_int() < 50) {
		command("say �ҵ��书��Ҫ���ߵ����Բ���ѧ�ᣨ����50����");
		command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
		command("say ��λ"+RANK_D->query_respect(ob)+"�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	if((int)ob->query("shen") < 2000){
		command("say �ҹ�Ĺ������Ȼ��ǿ�����񣬵�����������а����");
		command("say ��λ" + RANK_D->query_respect(ob)+"��������2k��ȥ������������º������ɣ�");
		return;
	}
	command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
	command("recruit " + ob->query("id"));
	ob->set("title","��Ĺ��������´���");
	//return "�ҹ�Ĺ�����˶���������Ҫ�ú�Ϊ�ҹ���ҹ�Ĺ��\n";
}

string ask_suo()
{
	object ob = this_player();
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "��Ĺ��" ||ob->query("family/master_name")!="С��Ů")
		return RANK_D->query_respect(ob)+"�����Ѿ�����δ�ý������ˣ�Ҳ��֪�����ںδ��ˡ�";
	if (ob->query_skill("yinsuo-jinling", 1) < 350)
		return "��λ"+ RANK_D->query_respect(ob) +"������������쳣�����Ƿ�Ӧ�ð��书����Щ��";
	ob->set_temp("marks/����", 1);
	command("nod " + ob->query("id"));
	return "�����������ͷ��ڴ����У����Ը����Ұɡ�";       
}

int pfm_yufeng()
{
	object me,weapon;
	me = this_object();
	weapon = present("changbian",me);
	if( me->is_busy()) return 0;
	if( me->query_temp("hebi")) return 0;
	if( objectp(weapon)){
		set("jiali", 1);
		command("wield bian");
		command("perform yufeng");
		if(random(10) > 5){
			set("jiali", 50);
			command("unwield bian");
		}
		return 1;
	}
	else {
		if(present("changbian", environment(me)))
		command("get bian");
		else new(BINGQI_D("whip"))->move(me);
		command("wield bian");
		set("jiali", 1);
		command("wield bian");
		command("perform yufeng");
		if(random(10) > 5){
			set("jiali", 50);
			command("unwield bian");
		}
		return 1;
	}
	return 1;
}

string ask_zhen()
{
	object me = this_player();
	object *list;
	int i, j=0;

	if (me->query("family/family_name") != "��Ĺ��"||me->query("family/master_name")!="С��Ů")
		return "�㲻���ҹ�Ĺ�ɴ��ˣ���Ҫ���������ã�";

	if( me->query("family/generation") > 4 )
		return "�����ڻ��ò�������롣";

	if (present("yufeng zhen",me))
		return "�����ϻ�������룬��ô����Ҫ��";

	if ( me->query_temp("yfzhen"))
		return "�㲻�Ǹ�Ҫ�����������ô����Ҫ��ô̰�İ���";

	list = filter_array(objects(), (: $1->query("id") == "yufeng zhen":));

	i =  sizeof(list);
	while (i--)
		j += list[i]->query_amount();

	if ( j > 61)
		return "��Ӵ��������Ѿ������ˣ���Ȼ���Ҫ�ɡ�";

	new("/d/gumu/obj/yfzhen")->move(this_object());
	command("give 10 yufeng zhen to " + me->query("id"));
	me->set_temp("yfzhen", 1);
	return "��Щ�����������ȥ�ðɣ�";
}

string ask_shoutao()
{
	object me = this_player();

	if (me->query("family/master_name")!="С��Ů")
		return ("���������ҹ�Ĺ�ɵı���㲢���ҵĴ��ˣ����ܸ��㣡");

	if (present("baijin shoutao",this_object())) {
		command("give baijin shoutao to " + me->query("id"));
		return("�����׾͸����ˣ����Ҫ���Ʊ��ܺã�");
	}
	else return ("�������ˣ������Ѿ��������������ˡ�");
}

string ask_yueyin()
{
	object me = this_player();
	mapping fam = me->query("family");
	object *dest;
	int i, j = 0;

	if (!fam || fam["family_name"] != "��Ĺ��"||fam["master_name"] != "С��Ů")
		return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";

	if(me->query_skill("yunu-xinjing", 1) < 150 )
		return "�����Ů�ľ��ȼ��������޷��������磬����������! ";

	if(me->query_skill("yinsuo-jinling", 1) < 150 )
		return "�����������ȼ�������������������ʽ��˵�ɡ� ";

	if(me->query("yueyin")) {
		command("? "+me->query("id"));
		return RANK_D->query_respect(me)+"�����Ѿ�����������������ô��";
	}

	if ( me->query_temp("yueyin/ask"))
		return "�㻹����ȥ������";

	dest = users();
	i = sizeof(dest);
	while(i--) {
		if (userp(dest[i]) && !wizardp(dest[i]) && dest[i]->query_temp("yueyin/ask"))
		j++;
	}
	if(j >= 1)
		return "�ţ������ڱȽ�æ����ָ���˱��ˣ���Ȼ��������ɡ�";

	command("say �ţ������������ǽ����������似�У�������������ʹ�ô˼��ɣ���������Ҫ�����ϰ��");
	me->set_temp("yueyin/ask", 1);
	return "��������Ƭ���ԣ��Ƚ��ʺ���������ר��ȥ�����ɣ��ɲ�Ҫ���Ǵ�һ������Ŷ��";
}

void kill_ob(object me)
{
	command("heng");
	command("throw yufeng zhen at " + me->query("id"));
	::kill_ob(me);
}


int ask_hubo()
{
	object me= this_player();
	if(!me->query_temp("marks/askzhou")|| me->query("gmhb"))
	{
		command("say ����ͯ��һ�ƴ�ʦ���������ڰٻ��������ӣ������ֲˣ�ݪ��������õ�Ҳ��ң���ڡ�");
	  	command("say ���пյ�ʱ�����ҵ�����������ȥ����̽����һ�°ɡ�");  
	  	return 1;
	}

    if( me->query_temp("marks/askzhou") )
    {
  	
  		command("say �ҹ�Ĺ����Ů�ľ������ı�������������������������������һ���֮�����ؼ�����ȫ�ڡ����Ķ��á����֣�������һ���ĵؿ����� ");
  		command("say ����������������Ĭ���������ʹ��Ů����������ʹȫ�潣����˫���������У���Ȼ��Ȼ��ͨ�� ");
		command("say ��Ͱ�����������������ҵ���ָ���㣬�ܷ�����Ϳ���������ˡ� ");
		command("say �𵽴����ܣ���������ǰ������̹���˫�ֻ�����֪ʶ�ɡ�");

		me->delete_temp("marks/askzhou");
		me->set_temp("tryhb",1);
		me->set("quest/gumu/tryhb",1);
		return 1;
  	}

		command("pat " + me->query("id"));
		return 1;	
	
}
string ask_qufengshu()
{
	object me=this_player();

	if (me->query_skill("qufengshu",1)<150)
	{
		command("say �������������̫�ͣ��Ҽ��㴫�ڸ��㣬Ҳûʲô���á�������150���������ҡ�\n");
		return "�����ȥͱͱ�䳲��˵���������ջ�\n";
	}
	if (me->query("quest/gm/ynxj/qufeng/pass"))
	{
		command("say ����������Ѿ�ѧ���ˣ��������ҡ�\n");
		return "�ϴ�С�ˣ�����ô��Ƥ��\n";
	}
	if (time()-me->query("quest/gm/ynxj/qufeng/time")<86400)
	{
		command("say ������Ѿ��ʹ��ü����ˡ�\n");
		return "�ϴ�С�ˣ�����ô��Ƥ��\n";
	}
	if (me->query("family/family_name")!="��Ĺ��"||me->query("family/master_name")!="С��Ů")
	{
		command("����ҹ�Ĺ�ɵ��ӣ�����������ⲻ���ú����ô��");
		return "�Ҵ��Ĺ���书����ޱȡ�\n";
	}
	command("say ��Ȼ����ѧϰ�����似���Ҿʹ������㣬�����ѱ��һ���۷䣬Ȼ�󲻶�ѵ���������������۷�ͻ��������ָ����.\n");
	command("say �����������ù������ӣ�����ѵ�����ԡ�\n");
	message_vision(HIY"\n\n\n\nС��Ů�ݸ�$Nһ�������ķ��䡣\n\n\n"NOR,me);
	call_out("xun_feng",1,me);
	return "";
}

int xun_feng(object me)
{
  int i,j; 
  if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
  
  if(me->query_temp("canwu_xunfeng")<(10+random(10)))
   {  
	  me->add_temp("canwu_xunfeng",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����С��Ů�Ľ�������С��Ů�����ڵ�ѵ�����˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ����ֻС������˵ط�����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ�����ôָ���۷�Ҳ������ָ�ӣ��������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ�����С�۷�̫��ͦ���ˣ��������.\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ��С���Խ��Խ��.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("xun_feng");
	  call_out("xun_feng",3+random(3), me);

   } 
   else if (i>25
			&& random(j)<6
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N����������������������С��Ů�����ڵ�ѵ�����Ŀھ����أ���\n"NOR,me); 
         log_file("quest/xlnxunfeng", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�����ѵ���������İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynxj/qufeng/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));
              
		 me->set("quest/gm/ynxj/qufeng/time",time());
		 me->set("quest/gm/ynxj/qufeng/pass",1);
		 me->delete_temp("canwu_xunfeng");

		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵������������ѵ�������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n����ѵ������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xlnxunfeng", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ���ѵ��������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynxj/qufeng/fail",1),
		 i,
		 j,
         me->query("combat_exp"),
		));        
		 me->add("quest/gm/ynxj/qufeng/fail",1);
		 me->set("quest/gm/ynxj/qufeng/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_xunfeng");
		 return 1;
   }

}

string ask_ynjfjj()
{
	object me=this_player();
	if (!me->query("quest/gumu/tryhb"))
	{
		command("say ������ȥ��Ѱ���ܲ�ͨ�����£���ȥ��ô��");
		return "��ô������ô��ƣ�ĵ���\n";
	}
	if (me->query_skill("yunu-jianfa",1)<500)
	{
		command("say �����Ů����̫�ͣ��Ҽ��㴫�ڸ��㣬Ҳûʲô���á�������500���������ҡ�\n");
		return "�����ȥ��ϰ�����ɡ�\n";
	}
	if (me->query_skill("yunu-xinjing",1)<500)
	{
		command("say �����Ů����̫�ͣ��Ҽ��㴫�ڸ��㣬Ҳûʲô���á�������500���������ҡ�\n");
		return "�����ȥ��ϰ�ڹ�ȥ�ɡ�\n";
	}
	if (me->query("quest/gm/ynjf/hubo/pass"))
	{
		command("say ���˫�ֻ����Ѿ�ѧ���ˣ��������ҡ�\n");
		me->set("mytitle/quest/ynjhubo",HIM"��Ĺ��Ů�����洫"NOR);
		return "�ϴ�С�ˣ�����ô��Ƥ��\n";
	}
	if (time()-me->query("quest/gm/ynjf/hubo/time")<86400)
	{
		command("say ������Ѿ��ʹ��ü����ˡ�\n");
		return "�ϴ�С�ˣ�����ô��Ƥ��\n";
	}
	if (me->query("family/family_name")!="��Ĺ��"||me->query("family/master_name")!="С��Ů")
	{
		command("����ҹ�Ĺ�ɵ��ӣ�����������ⲻ���ú����ô��");
		return "�Ҵ��Ĺ���书����ޱȡ�\n";
	}
	if (!me->query("hubo/givejunzi"))
	{
		if (me->query("gender")=="Ů��")
			command("say �ðɣ��������ȥѰ����Ů��������Ů��������Ϊ����׼�������");
		else command("say �ðɣ��������ȥѰ�Ҿ��ӽ�������ӽ�������Ϊ����׼�������");
		return "������Ů�����������Ҵ��Ĺ�ı�־ô��";
	}
	command("say ��Ȼ����ѧϰ�����似���Ҿʹ�������,�������Ҳ��ѧ���ܲ�ͨ��.\n");
	command("say ��ѧ�����������似�ģ�һΪ���ɵ���Ů�ľ�����������������ﵽ�ľ����飬����һ�Ź���������칦��\n");
	command("say �����������������⣬��������ͯѵ����䣬��ͬʱ���ڸ��ҵ����ž�����\n");
	command("say ��ɿ����ˣ������������Ů�ľ����ռ����ء�\n");
	message_vision(HIY"\n\n\n\nС��Ůˢ�س�����ѽ�,��Ů�ľ����һ�µĹ�����ԣ�ɲ�Ǽ佣���ݺᡣ\n\n\n"NOR,me);
	remove_call_out("think_hubo");
	call_out("think_hubo",1,me);
	return ""; 
}

int think_hubo(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;


  if(me->query_temp("canwu_hubo")<(10+random(10)))
   {  
	  me->add_temp("canwu_hubo",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ�˫�ֻ����˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("think_hubo");
	  call_out("think_hubo",3+random(3), me);

   } 
   else if (i >= 26
	        && me->query("kar") <31
	        && random(j) <5
	        && random(me->query("int")) > 40)
 	{ 
        
         me->start_busy(1);     
         message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N����������������������С��Ů�����ڵ�˫�������ĵĿھ����أ���\n"NOR,me); 
		 message_vision(HIY"\n$N��Ȼ�����ⲻ���ǹ�Ĺ����Ů�ľ����һ�µ��书ô������\n"NOR,me); 
         log_file("quest/gumuhubo", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�˫�ֻ��������İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynjf/hubo/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/gm/ynjf/hubo/time",time());
		 me->set("quest/gm/ynjf/hubo/pass",1);
		 me->set("title",HIM"��Ĺ��Ů�����洫"NOR);
		 me->set("mytitle/quest/ynjhubo",HIM"��Ĺ��Ů�����洫"NOR);
		 me->delete_temp("canwu_hubo");

		 return 1;
     }
	 else {
		 message_vision(HIG"\n$N˫����ʹ����ôҲ����������˫�ָ�����ʹ�����ļ��ɣ��ü��β�������Լ�����\n"NOR,me); 
	     message_vision(HIG"\n$N��̾һ�������������˵��������������Ů�ľ����һ�µ��书���ǲ�������������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n������Ů����˫�ֻ�����������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/gumuhubo", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�����Ů����˫�ֻ�����������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/gm/ynjf/hubo/fail",1),
		 i,
		 j,
         me->query("combat_exp"),
		));        
		 me->add("quest/gm/ynjf/hubo/fail",1);
		 me->set("quest/gm/ynjf/hubo/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_hubo");
		 return 1;
   }

}
int accept_object(object me, object obj,object ob)
{
	ob = this_object();
		
	if (me->query("gender")=="����" &&obj->query("id")=="junzi jian")
	{
		message_vision(HIC"$N��������ӽ��������У�������ȥ�Ĺۿ���������ɫ���ǻ�ϲ��\n"NOR,ob);
		command("say ��ѽ�����Ϭ���ޱȣ���ô�����ˣ���Ȼ������˵ķ�����\n");
		command("say �ţ���Ȼ����ô���ģ��Ҿ�������С�����ˡ�\n");
		message_vision(HIC"$N��������ӽ����뽣�ʣ�˳���ӵ�һ�ԣ�������ᣬ�������̬������������ת��\n"NOR,ob);
		me->set_temp("hubo/givejunzi",1);
		me->set("hubo/givejunzi",1);
		destruct(obj);
		return 1;

	}
	if (me->query("gender")=="Ů��" &&obj->query("id")=="shunu jian")
	{
		message_vision(HIC"$N�������Ů���������У�������ȥ�Ĺۿ���������ɫ���ǻ�ϲ��\n"NOR,ob);
		command("say ��ѽ�����Ϭ���ޱȣ���ô�����ˣ���Ȼ������˵ķ�����\n");
		command("say �ţ���Ȼ����ô���ģ��Ҿ�������С�����ˡ�\n");
		message_vision(HIC"$N�������Ů�����뽣�ʣ�˳���ӵ�һ�ԣ�������ᣬ�������̬������������ת��\n"NOR,ob);
		me->set_temp("hubo/givejunzi",1);
		me->set("hubo/givejunzi",1);
		destruct(obj);
		return 1;

	}

}