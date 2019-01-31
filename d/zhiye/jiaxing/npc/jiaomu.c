// jiaomu.c ��ľ
// Created by sohu@xojh

inherit NPC;
#include <ansi.h>
string ask_duan();
string ask_daole();
string ask_pingli();

void create()
{
   set_name("��ľ��ʦ",({"jiaomu dashi","jiaomu","dashi"}));
   set("gender","����");
   set("long","���������֣���ľ��ʦ�����ô˴�ü��Ŀ�����ǰ���!\n");
   set("shen",80000);
   set("combat_exp",1200000);
   //set("nickname","����������");
   set("title","����������");
   
   set("age",30);
   set("pur",12);
   set("kar",20);
   set("per",25);
   set("str",30);
	 set("int",25);
	 set("con",20);
	 set("dex",30);
	 set("max_qi", 3000);
	 set("max_jing", 3000);
	 set("eff_jingli", 3000);
	 set("neili", 2000);
	 set("max_neili", 2000);
	 set("jiali", 100);

   set_skill("dodge",350);
   set_skill("force",350);
   set_skill("parry",350);
   set_skill("sword",350);
   set_skill("cuff",300);
   //set_skill("stealing",380);
   set_skill("luohan-quan",350);
   set_skill("literate",200);
   set_skill("xiaoyaoyou",350);
   map_skill("dodge","xiaoyaoyou");
   map_skill("cuff","luohan-quan");
   setup();
   set("inquiry", ([
          "�����" : (: ask_duan :),
		  "���Ѿ�����" : (: ask_daole :),
		  "����" : (: ask_pingli :),
   ]) );
   setup();
   add_money("silver",70);
	carry_object("d/jiaxing/obj/cloth")->wear();
	carry_object("d/menggu/npc/obj/zheshan");
}
string ask_duan()
{
	object me,jiaomu;
	me=this_player();
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/findfahuasi"))
	{
		command("say �����ӷ��������գ�\n");

		return "�α���˴󶯸λ��������գ�\n";
	}
	
	message_vision(HIY"\n$N��������Լ������Ů����������ȷ��������ľ����һζ�ĵ������ϣ�Ҳ��ŭ������!\n"NOR,me);
	message_vision(HIW"\n��ʱ�򣬾�����ľ����˵��������Ȼ��һ��ҧ���������������Ҫ�ҵ��ˣ�\n��ô��ʱ���ҵ���������¥���뽭���߹ֵ�������ʿ�ֳ�������֤��Σ���\n"NOR,me);
	message_vision(HIG"\n�����зߺޣ�һ�ı�����������ʲô�����߹֣�Ҳ���ý�������и�ɱ�ˣ����Ǿʹ�Ӧ������\n"NOR,me);
	message_vision(HIR"\n��֪������бض������뽭��ͬ�����ֺ��Լ���ս�����Լ����º���������������Ҳ��ɱɱ���ǵ�ʿ����\n"NOR,me);
	message_vision(HIR"\n���ͷ�����ſڷ�����һ�ڻ�ֽ�Ĵ�ͭ�ף����������Լ�Ӧ���ܾ�������\n"NOR,me);

	
	me->set_temp("quest/���Ӣ�۴�/�����߹�/askjiaomu",1);
	return "����������������\n";

}
string ask_pingli()
{
	object me,jiaomu;
	me=this_player();
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/qiguaicome"))
	{
		command("say ��ɮ�����Ͷ٣�û�±����ʣ�\n");

		return "�α���˴󶯸λ��������գ�\n";
	}
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/pingli"))
	{
		command("say ���Ų��Ǹ�������ô��\n");

		return "�������գ�\n";
	}
	message_vision(HIY"\n\n$N˵���������ºͽ�ľ��ʦ�ز���ʶ����ԩ�޳�ֻҪ�����������������������Իᵽ�������¸��������\n"
						"��������������ʲô��������,$N˵�������������������ѣ����˹ٸ��ͽ�����ݺ����������ڷ���������\n"
						"���µĹѸ��¿��������´���������˵���¸ò������� ֻ��������������˵�ǵ������ѵ����ף�������\n"
						"����ʶ֮�ˣ����Ǽ�Ȼ֪���ˣ�Ҳ�������չˣ������岻�ݴ�֮�¡���$N������������ѽ���Ҿ���Ҫ��ľ��ʦ\n"
						"������������������Ů���������ǳ����ˣ�ȴ���Խ������Ѹ�����������ǲ��Ͻ�������λ������֮�ˣ�\n"
						"���������������\n\n"NOR,me);
	command("say �㡭���㡭�������ҵ��������ԡ�����\n");
	
	message_vision(HIR"\n$N���Ľ�ľ��ʦ��˱�⣬���д�ŭ�����鼤��֮�£������о��ŵ�ͭ������ľ��ʦ��\n"NOR,me);
	message_vision(HIR"\nվ��¥ͷ�����ֵ����ŵû�����⣬������ӵ��һ�����Ĺ�µµ����¥ȥ��\n"NOR,me);
	me->delete_temp("quest/���Ӣ�۴�/�����߹�/qiguaicome");
	me->set_temp("quest/���Ӣ�۴�/�����߹�/pingli",1);
	message_vision(MAG"\nЦ�����Ű���������ͭ�����أ��Լ����ɽӵ�ס����������һ��������˫�ۣ���һ�������ã���\n"
						"��ͭ�׷ɵ���˫��һ������ס�׵ף��米������𣬾��԰�ͭ�׽�ס�ˣ�˫������һͦ����ͭ��\n"
						"�߾ٹ�������������ʹ��̫�ޣ�����һ����������¥����̤����һ������¥�������ִ��������\n"
						"�Ű�����ǰ������˫��΢����һ�С��ƴ����¡�����ͭ����$N��ȥ��\n"NOR,me);
	message_vision(HIG"\n$N���ֽӹ����ͭ�ף���̾�����������߹ֹ�Ȼ�����鴫����\n"
						"$N��˫�����ֲ��£��˴˲����ˣ��������ǲ������ˣ���������Ц��������Ȼ��λӢ���ڳ���\n"
						"���Ǿ�����ʶ�£������θ���λӢ�۾��ƣ������������ֽ��ϼ����£�\n"
						"\n�����߹־㶼��ͷ��ͬ��\n"NOR,me);
	me->set_temp("quest/���Ӣ�۴�/�����߹�/pingli",1);
	return "�����ӷ�\n";

}

string ask_daole()
{
	object me,jiaomu;
	me=this_player();
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/fanggangwait"))
	{
		command("say ��ɮ�����Ͷ٣�û�±����ʣ�\n");

		return "�α���˴󶯸λ��������գ�\n";
	}
	command("say ʩ������ǿ��ѹ�ˣ�����Ҳ��һ�ִȱ���\n");
	command("buddhism ");
	command("say �Ե�Ƭ�̣������˽���ͬ��һ��������֤��\n");
	call_out("han_come",3+random(3),me);
	me->set_temp("quest/���Ӣ�۴�/�����߹�/qiguaicome",1);
	return "�����ӷ�\n";

}

int han_come(object me)
{
	object han;
	if (!me||file_name(environment(me))!="/d/jiaxing/jxyanyu2") return 0;
	
	if (!objectp(han=present("han baoju",environment(this_object()))))
	{
		han=new("d/jiaxing/npc/hanbaoju");
		han->move(environment(this_object()));
	}
	message_vision(HIR"\nͻȻ��ǰ���������٣�һ�������������нֱ���������֮����ӵ���������ְ����������̯ͷ����\n"
					  "��ο��Գ���$Næ��ֱ�һ����ת��֮�䣬��һƥ������˴���ֱ�ܳ������������쳣\n"
					  "��߱�ʣ�����һƥ������������������񿥣�����֮��ȴ�Ǹ��ְ����ֵ�������ӣ�������������\n"
					  "��������һ�㡣�����ֶ���̣�û�в��ӣ�һ��ͷ��ĳ��棬ȴ������˫��֮�С�˵Ҳ��֣��������˶�\n"
					  "�﷢�㼱����ȴ������һ�ˡ��಻�߷�һ�ֻ����������ӯ����Ծ���磬���������ѣ������˵���ÿÿ\n"
					  "�ڼ䲻�ݷ�֮�����ö��������м����������Ұ�۳����졣\n"NOR,me);
   message_vision(WHT"\n\n�ǰ�����ת�����ڣ���һ�����һ������һ���������ڹ��ϣ�˵���������������ϵȾƲˣ�������ģ�\n"
						"һ���صġ����ƹ��Ц����������������ү��������ɽ������������㣬�¾��ٺ�û�С�������������ү�����ţ�\n"
						"�������㡣�������Ӱ���һ���������ȵ�������ô���ȾƲ���Ǯ���㵱����ү�ǹ����죬�԰�ʳ��ô�����ƹ�Ц\n"
						"������Ҳ����Ϊ�裬�����е���������ǣ��ӰѾ�������ү���ξƲ��ģ����ڻ����������һ�������Ĵ�Ӧ��\n"NOR,me);
	call_out("xiaoying_come",4+random(3),me);
	return 1;
}
int xiaoying_come(object me)
{
	object ying,nan;
	if (!me||file_name(environment(me))!="/d/jiaxing/jxyanyu2") return 0;
	if (!objectp(ying=present("han xiaoying",environment(this_object()))))
	{
		ying=new("d/jiaxing/npc/hanxiaoying");
		ying->move(environment(this_object()));
	}
	if (!objectp(nan=present("nan xiren",environment(this_object()))))
	{
		nan=new("d/jiaxing/npc/nanxiren");
		nan->move(environment(this_object()));
	}
	message_vision(HIC"\n\n����������һҶ������ɰ㻮���������۴�����������ͷ�߸����𣬴�����ͣ������׽���ˮ��\n"
					  "$N��ʱҲ�����⣬��ת��֮�䣬ֻ���������ѸϹ���Զ��ǰͷ��С�������ǿ�ó��档\n"
					  "Ƭ�̼����۽���������������һ�ˣ���β�����Ĵ���һ�����£�ȴ�Ǹ�Ů�ӡ�\n"
					 NOR,me);
   message_vision(YEL"\nֻ�����������⣬�����ѽ���¥���չ����ڽ��ϣ����λε�ԭ����һ��ͭ����ͭ��������Ů������ϵ��\n"
						"��¥��ʯ���Ե�ľ׮�ϣ���Ծ�ǰ������ڴ�����ĺ�������һ���ֲ�Ҳ�����������������Ͼ�¥����Ů\n"
						"���ǰ����ӽ������������磡�������������������������ӵ������ĵܡ����ã����������磡��\n"
						NOR,me);
	call_out("qz_come",4+random(3),me);
	return 1;
}
int qz_come(object me)
{
	object quan,zhang;
	if (!me||file_name(environment(me))!="/d/jiaxing/jxyanyu2") return 0;
	
	if (!objectp(quan=present("quan jinfa",environment(this_object()))))
	{
		quan=new("d/jiaxing/npc/quanjinfa");
		quan->move(environment(this_object()));
	}
	if (!objectp(zhang=present("zhang asheng",environment(this_object()))))
	{
		zhang=new("d/jiaxing/npc/zhangasheng");
		zhang->move(environment(this_object()));
	}
	message_vision(HIC"\n\n���˸�������¥�½Ų����죬�������ˡ�����Ů�е�������硢���磬����һ����������ǰ��\n"
					  "һ����Ŀ��࣬��˵Ҳ�ж�������ʮ�Χ��һ����Χȹ��ȫ�����壬�����½�¶��ë��\n"
					  "�׵����ţ����Ӿ�ø߸ߵģ��ֱ���ȫ�Ǵ����ĺ�ë������Ƥ���ϲ��ű��������ļ⵶��\n"
					 "��ģ���Ǹ�ɱ����������򡣺������������ģ�ͷ��Сձñ���׾���Ƥ����������һ�˳�\n"
					 "һ����¨�����Ǹ�С�̷���$N�������棺����ͷ�����˶��������书֮�ˣ���ô������\n"
					 "�о�С��ȴ�ָ������ֵ���ƣ���\n"NOR,me);
  
	call_out("kz_come",4+random(3),me);
	return 1;
}

int kz_come(object me)
{
	object ke,zhu;
	if (!me||file_name(environment(me))!="/d/jiaxing/jxyanyu2") return 0;
	
	if (!objectp(ke=present("ke zhene",environment(this_object()))))
	{
		ke=new("d/jiaxing/npc/kezhene");
		ke->move(environment(this_object()));
	}
	if (!objectp(zhu=present("zhu cong",environment(this_object()))))
	{
		zhu=new("d/jiaxing/npc/zhucong");
		zhu->move(environment(this_object()));
	}
	message_vision(HIC"\n\n�������ϴ���һ��ǵǵ�֮�������������û�ʯ�壬�����û�������¥�ݣ�����һ��������\n"
					  "�ڵ�Ϲ�ӣ���������һ���ִ�����ȡ�ֻ������ʮ������ͣ�������������ɫ�����˵أ�����\n"
					  "�׶�̬֮���������ߵ����˶�վ����������У�����硣����Ů��һ������������һ�ģ�����\n"
					 "����磬����λ���������Ϲ�ӵ������á����ܻ�û��ô����������ģ�����˵����������ѵ���\n"
					 "���ˣ����Ҳ������������ŮЦ�������ⲻ�������𣿡�ֻ����¥����һ����̤��̤��ЬƤ���졣\n"
					  NOR,me);
   
	return 1;

}