// jiaomu.c 焦木
// Created by sohu@xojh

inherit NPC;
#include <ansi.h>
string ask_duan();
string ask_daole();
string ask_pingli();

void create()
{
   set_name("焦木大师",({"jiaomu dashi","jiaomu","dashi"}));
   set("gender","男性");
   set("long","法华寺主持，焦木大师，长得此慈眉善目，甚是安详!\n");
   set("shen",80000);
   set("combat_exp",1200000);
   //set("nickname","法华寺主持");
   set("title","法华寺主持");
   
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
          "段天德" : (: ask_duan :),
		  "我已经到了" : (: ask_daole :),
		  "评理" : (: ask_pingli :),
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
	if (!me->query_temp("quest/射雕英雄传/江南七怪/findfahuasi"))
	{
		command("say 阿弥陀佛，善哉善哉！\n");

		return "何必如此大动肝火，善哉善哉？\n";
	}
	
	message_vision(HIY"\n$N方才是隐约听到有女声，但并不确定，而枯木道长一味的抵赖不认，也是怒火万丈!\n"NOR,me);
	message_vision(HIW"\n这时候，就听枯木道长说道，“既然你一口咬定是我庙里藏着你要找的人，\n那么午时你我到嘉兴烟雨楼，请江南七怪等武林人士现场做个见证如何？”\n"NOR,me);
	message_vision(HIG"\n你心中愤恨，一心报仇，哪里晓得什么江南七怪，也不好将这个和尚给杀了，于是就答应下来。\n"NOR,me);
	message_vision(HIR"\n你知道这和尚必定是邀请江南同道好手和自己对战，但自己又怕何来？有心立威，也好杀杀他们的士气！\n"NOR,me);
	message_vision(HIR"\n你低头看到门口放置了一口化纸的大铜缸，评估了下自己应该能举起来！\n"NOR,me);

	
	me->set_temp("quest/射雕英雄传/江南七怪/askjiaomu",1);
	return "这人真是蛮不讲理！\n";

}
string ask_pingli()
{
	object me,jiaomu;
	me=this_player();
	if (!me->query_temp("quest/射雕英雄传/江南七怪/qiguaicome"))
	{
		command("say 老僧甚是劳顿，没事别乱问！\n");

		return "何必如此大动肝火，善哉善哉？\n";
	}
	if (me->query_temp("quest/射雕英雄传/江南七怪/pingli"))
	{
		command("say 方才不是告诉你了么！\n");

		return "善哉善哉？\n";
	}
	message_vision(HIY"\n\n$N说道：“在下和焦木大师素不相识，无冤无仇，只要他交出两个人来，改日我自会到法华禅寺负荆请罪。”\n"
						"柯镇恶道：“交出什么人来？”,$N说道：“在下有两个朋友，受了官府和金兵的陷害，不幸死于非命。他们\n"
						"遗下的寡妇孤苦无依。柯大侠，你们说在下该不该理？” 只听柯镇恶道：“别说是道长朋友的遗孀，就是素\n"
						"不相识之人，咱们既然知道了，也当量力照顾，那是义不容辞之事。”$N大声道：“是呀！我就是要焦木大师\n"
						"交出两个身世可怜的女子来；他是出家人，却何以将两个寡妇收在寺里，定是不肯交出？七位是侠义之人，\n"
						"请评评这道理看！”\n\n"NOR,me);
	command("say 你……你……胡言乱道……胡言……！\n");
	
	message_vision(HIR"\n$N听的焦木大师如此辩解，心中大怒，心情激荡之下，将手中举着的铜缸推向焦木大师！\n"NOR,me);
	message_vision(HIR"\n站在楼头看热闹的人吓得魂飞天外，你推我拥，一连串的骨碌碌滚下楼去。\n"NOR,me);
	me->delete_temp("quest/射雕英雄传/江南七怪/qiguaicome");
	me->set_temp("quest/射雕英雄传/江南七怪/pingli",1);
	message_vision(MAG"\n笑弥陀张阿生估量这铜缸虽重，自己尽可接得住，当下抢上一步，运气双臂，叫一声：“好！”\n"
						"待铜缸飞到，双臂一沉，托住缸底，肩背肌肉坟起，竟自把铜缸接住了，双臂向上一挺，将铜缸\n"
						"高举过顶。但他脚下使力太巨，喀喇一声，左足在楼板上踏穿了一个洞，楼下众人又大叫起来。\n"
						"张阿生上前两步，双臂微曲，一招“推窗送月”，将铜缸向$N掷去。\n"NOR,me);
	message_vision(HIG"\n$N伸手接过这个铜缸，赞叹道，“江南七怪果然名不虚传”！\n"
						"$N见双方僵持不下，彼此不认账，不动手是不可能了，于是朗声笑道，“既然各位英雄在场”\n"
						"咱们就先认识下，我依次给各位英雄敬酒，喝完了咱们手脚上见真章！\n"
						"\n江南七怪俱都点头赞同！\n"NOR,me);
	me->set_temp("quest/射雕英雄传/江南七怪/pingli",1);
	return "阿弥陀佛！\n";

}

string ask_daole()
{
	object me,jiaomu;
	me=this_player();
	if (!me->query_temp("quest/射雕英雄传/江南七怪/fanggangwait"))
	{
		command("say 老僧甚是劳顿，没事别乱问！\n");

		return "何必如此大动肝火，善哉善哉？\n";
	}
	command("say 施主，别强势压人，放下也是一种慈悲！\n");
	command("buddhism ");
	command("say 稍等片刻，我请了江南同道一起做个见证！\n");
	call_out("han_come",3+random(3),me);
	me->set_temp("quest/射雕英雄传/江南七怪/qiguaicome",1);
	return "阿弥陀佛！\n";

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
	message_vision(HIR"\n突然间前面蹄声急促，一骑马急奔而来。市街本不宽敞，加之行人拥挤，街旁又摆满了卖物的摊头担子\n"
					  "如何可以驰马？$N忙向街边一闪，转眼之间，见一匹黄马从人丛中直窜出来。那马神骏异常\n"
					  "身高膘肥，竟是一匹罕见的良马。那马如此神骏，骑马之人却是个又矮又胖的猥琐汉子，乘在马上犹如\n"
					  "个大肉团一般。此人手短足短，没有脖子，一个头大的出奇，却又缩在双肩之中。说也奇怪，那马在人堆\n"
					  "里发足急奔，却不碰到一人、亦不踢翻一物，只见它出蹄轻盈，纵跃自如，跳过瓷器堆，跨过青菜担，每每\n"
					  "在间不容发之际闪让而过，闹市疾奔，竟与旷野驰骋无异。\n"NOR,me);
   message_vision(WHT"\n\n那矮胖子转身入内，手一扬，当的一声，将一大锭银子掷在柜上，说道：“给开三桌上等酒菜，两桌荤的，\n"
						"一桌素的。”掌柜的笑道：“是啦，韩三爷。今儿有松江来的四鳃鲈鱼，下酒再好没有。这银子您韩三爷先收着，\n"
						"慢慢再算。”矮胖子白眼一翻，怪声喝道：“怎么？喝酒不用钱？你当韩三爷是光棍混混，吃白食的么？”掌柜笑\n"
						"嘻嘻的也不以为忤，大声叫道：“伙计们，加把劲给韩三爷整治酒菜哪！”众伙计里里外外一叠连声的答应。\n"NOR,me);
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
	message_vision(HIC"\n\n忽见湖心中一叶渔舟如飞般划来。这渔舟船身狭长，船头高高翘起，船舷上停了两排捉鱼的水鸟。\n"
					  "$N初时也不在意，但转眼之间，只见那渔舟已赶过了远在前头的小船，竟是快得出奇。\n"
					  "片刻间渔舟渐近，见舟中坐着一人，舟尾划桨的穿了一身蓑衣，却是个女子。\n"
					 NOR,me);
   message_vision(YEL"\n只见她又是数扳，渔舟已近酒楼，日光照在桨上，亮晃晃的原来是一柄铜铸的铜桨。那渔女把渔舟系在\n"
						"酒楼下石级旁的木桩上，轻跃登岸。坐在船舱里的汉子挑了一担粗柴，也跟着上来。两人迳上酒楼。渔女\n"
						"向那矮胖子叫了声：“三哥！”在他身旁坐了下来。矮胖子道：“四弟、七妹，你们来得早！”\n"
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
	message_vision(HIC"\n\n两人刚坐定，楼下脚步声响，上来两人。那渔女叫道：“五哥、六哥，你们一齐来啦。”前面\n"
					  "一人身材魁梧，少说也有二百五六十斤，围着一条长围裙，全身油腻，敞开衣襟，露出毛茸\n"
					  "茸的胸膛，袖子卷得高高的，手臂上全是寸许长的黑毛，腰间皮带上插着柄尺来长的尖刀。\n"
					 "瞧模样是个杀猪宰羊的屠夫。后面那人五短身材，头戴小毡帽，白净面皮，手里提了一杆秤\n"
					 "一个竹篓，似是个小商贩。$N暗暗称奇：“瞧头上三人都是身有武功之人，怎么这两个\n"
					 "市井小人却又跟他们兄弟相称？”\n"NOR,me);
  
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
	message_vision(HIC"\n\n忽听街上传来一阵登登登之声，似是铁物敲击石板，跟着敲击声响上楼梯，上来一个衣衫褴\n"
					  "褛的瞎子，右手握着一根粗大的铁杖。只见他四十来岁年纪，尖嘴削腮，脸色灰扑扑地，颇有\n"
					  "凶恶之态。坐在桌边的五人都站了起来，齐叫：“大哥。”渔女在一张椅子上轻轻一拍，道：\n"
					 "“大哥，你座位在这里。”那瞎子道：“好。二弟还没来么？”那屠夫模样的人道：“二哥已到了\n"
					 "嘉兴，这会也该来啦。”渔女笑道：“这不是来了吗？”只听的楼梯上一阵踢踏踢踏拖鞋皮声响。\n"
					  NOR,me);
   
	return 1;

}