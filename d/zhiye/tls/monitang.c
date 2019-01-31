//cre by sohu@xojh,2014
// monitang.c 六脉 vs 火焰刀

#include <ansi.h>
#include "monitang.h"
inherit ROOM;
int do_fight1();
int do_jiejiu(string arg);
int do_baijian(string arg);
int do_bijian();
int check_hyd(object me,object bencan,object benguan,object benxiang,object benyin,object benchen,object kurong);

void create()
{
        set("short", HIY"牟尼堂"NOR);
        set("long",@LONG
这是天龙寺高僧们的静修之处，全以松木所制，板门木柱，木料均不去
皮，天然质朴，和一路行来金碧辉煌的殿堂截然不同。室中蒲团上分坐着三
个白须白眉的老和尚。
LONG
        );
		set("busy",1);
        set("exits", ([
		"out": __DIR__"lang2",
	]));
	set("objects",([
		__DIR__"npc/ben-guan" : 1,
		__DIR__"npc/ben-xiang" : 1,
		__DIR__"npc/ben-can" : 1,
		//__DIR__"npc/obj/ztnianzhu" : 1,
        ]));
        setup();
}
//本尘 保定帝。。带人来牟尼堂求见枯荣。
//本参 shaoze，本观斗鸠摩智，少冲剑法
//本因 shangyang,本尘 关冲剑

void init()
{
	   //接口，源自枯荣大师的ask kurong about 救治。。。。确保只有一个人在做
		object me,kurong,bencan,benguan,benxiang,benchen,benyin;
		object ztzhu;
		me=this_player();
		ztzhu=new("d/tls/npc/obj/ztnianzhu");
//注意要消掉初始变量
			
		if (present("zitan nianzhu",environment(me))&&(me->query_temp("tls/fight1")||me->query_temp("hydjj/receive")))
		{
				message_vision(HIC"现在有人正在解密，待会再来！\n"NOR,me);
				
				return;
		}			
	
        //解密六脉接口    
		if (!present("zitan nianzhu",environment(me))&&me->query_temp("tls/fight1"))
		{
			me->delete_temp("tls/fight1");
			call_out("do_1",1,me);
			
			ztzhu->move(environment(me));
			me->start_busy(999);
			return;
			//me->delete_temp("tls/fight1");
		}
		//解密火焰刀接口
		if (!present("zitan nianzhu",environment(me))&&me->query_temp("hydjj/receive"))
		{
			
			add_action("do_baijian","baijian");
			
			ztzhu->move(environment(me));
			
			if (!objectp(bencan=present("bencan dashi",environment(me))))
			{
				bencan=new("d/tls/npc/ben-can");
				bencan->move(environment(me));		
			}
	
			if (!objectp(benguan=present("benguan dashi",environment(me))))
			{
				benguan=new("d/tls/npc/ben-guan");
				benguan->move(environment(me));
			}
			if (!objectp(benyin=present("benyin dashi",environment(me))))
			{
				benyin=new("d/tls/npc/ben-yin");
				benyin->move(environment(me));
			}
			if (!objectp(benxiang=present("benxiang dashi",environment(me))))
			{
				benxiang=new("d/tls/npc/ben-xiang");
				benxiang->move(environment(me));
			}
			if (!objectp(kurong=present("kurong zhanglao",environment(me))))
			{
				kurong=new("d/tls/npc/kurong");
				kurong->move(environment(me));
			}
			if (!objectp(benchen=present("duan zhengming",environment(me))))
			{
				benchen=new("d/dali/dlhg/npc/duanzm");
				benchen->move(environment(me));
			}
			//me->start_busy(2);
			return;


		}
		
}

int do_1(object me)
{
    message_vision(HIC"便在此时，$N鼻端忽然闻到一阵柔和的檀香，跟着一声若有若无的梵唱远远飘来。\n"NOR,me);
    call_out("do_2",random(3),me);
	return 1;

}
int do_2(object me)
{
	message_vision(HIC"\n\n\n枯荣大师说道，“善哉，善哉！大明轮王驾到。我不想走动，便请明王到牟尼堂来叙会吧。”。\n"NOR,me);
    call_out("do_3",random(4),me);
	return 1;

}
int do_3(object me)
{
	message_vision(YEL"\n\n\n枯荣大师道：“$N，你坐在我身前，那大轮明王再厉害，也不能伤了你一要毫毛。”\n他声音仍是冷清冰冰的，但语意中颇有傲意。\n"NOR,me);
    call_out("do_4",random(4),me);
	return 1;

}

int do_4(object me)
{
	message_vision(HIY"\n\n\n门开后进来一个僧人，身穿黄色僧袍。不到五十岁年纪，布衣芒鞋，脸上神采飞扬，隐隐似有宝光流动，\n"+
				"便如是明珠宝玉，自然生辉。段誉向他只瞧得几眼，便心生钦仰亲近之意。再从板门中望出去，只见门外站\n"+
				"着八九个汉子，面貌大都狰狞可畏，不似中土人士，自是大轮明王从吐蕃国带来的随从了。\n"NOR,me);
	call_out("do_5",random(4),me);
	return 1;
}
int do_5(object me)
{
	tell_object(me,HIC"\n\n\n过了好一会，只听得本因方丈道：“明王法驾，请移这边牟尼堂。”另一个声音道：“有劳方丈领路。”段誉听\n"
				+"这声音甚是亲切谦和，彬彬有礼，绝非强凶霸横之人。听脚步声共有十来个人。听得本因推开板门，说道：“明王请！”\n"
				+"大轮明王道：“得罪！”举步进了堂中，向枯荣大师合什为礼，说道：“吐蕃国晚辈鸠摩智，参见前辈大师。有常\n"
				+"无常，双树枯荣，南北西东，非假非空！”枯荣大师却心中一惊：“大轮明王博学精深，果然名不虚传。他一见在\n"+
				"面便道破了我所参枯禅的来历。”世尊释迦牟尼当年在拘尸那城娑罗双树之间入灭，东西南北，各有双树，每一面的\n"
				HIG+"\n\n\n两株树都是一荣一枯，称之为‘四枯四荣’，据佛经中言道：东方双树意为‘常与无常’，南方双树意为‘乐与无乐’，\n"
				+"西方双树意为‘我与无我’，北方双树意为‘净与无净’。茂盛荣华之树意示涅般本相：常、乐、我、净；枯萎凋残之树\n"
				+"显示世相：无常、无乐、无我、无净。如来佛在这八境界之间入灭，意为非枯非荣，非假非空。枯荣大师数十年静参\n"
				+"枯禅，还只能修到半枯半荣的境界，无法修到更高一层的‘非枯非荣、亦枯亦荣’之境，是以一听到大轮明王的话，便即\n"
				+"凛然，说道：“明王远来，老衲未克远迎。明王慈悲。”\n"NOR);
	call_out("do_6",random(4),me);
	return 1;
}
int do_6(object me)
{
	message_vision(MAG"\n\n\n鸠摩智道：“小僧年轻识浅，所言未必能取信于众位大师。少林七十二绝技中的三门指法，不妨先在众位之前献丑。”\n"+
				"说着站起身来，说道：“小僧当年不过是兴之所至，随意涉猎，所习甚是粗疏，还望众位指点。这一路指法是拈花指。”\n"+
				"只见他右手拇指和食指轻轻搭住，似是拈住了一朵鲜花一般，脸露微笑，左手五指向右轻弹。\n"NOR,me);
	message_vision(HIC"\n\n\n可是鸠摩智弹指之间却不见得具何神通，他连弹数十下后，举起右手衣袖，张口向袖子一吹，霎时间袖子上飘下\n"
				+"一片片棋子大的圆布，衣袖上露出数十个破孔。原来他这数十下拈花指，都凌空点在自己衣袖之上，柔力损衣，\n"
				+"初看完好无损，一经风吹，功力才露了出来。本因与本观、本相、本参、保定帝等互望见了几眼，都是暗暗惊异：\n"
				+"“凭咱们的功力，以一阳指虚点，破衣穿孔，原亦不难，但出指如此轻柔软，温颜微笑间神功已运，却非咱们所能。\n"
				+"这拈花指与一阳指全然不同，  其阴柔内力，确是颇有足以借镜之处。”\n"NOR,me);
	call_out("do_7",random(4),me);
	return 1;
}
int do_7(object me)
{
	message_vision(HIG"\n\n\n鸠摩智道：“小僧年轻识浅，所言未必能取信于众位大师。少林七十二绝技中的三门指法，不妨先在众位之前献丑。”\n"+
				"说着站起身来，说道：“小僧当年不过是兴之所至，随意涉猎，所习甚是粗疏，还望众位指点。这一路指法是拈花指。”\n"+
				"只见他右手拇指和食指轻轻搭住，似是拈住了一朵鲜花一般，脸露微笑，左手五指向右轻弹。\n"NOR,me);
	message_vision(HIC"\n\n\n可是鸠摩智弹指之间却不见得具何神通，他连弹数十下后，举起右手衣袖，张口向袖子一吹，霎时间袖子上飘下\n"
				+"一片片棋子大的圆布，衣袖上露出数十个破孔。原来他这数十下拈花指，都凌空点在自己衣袖之上，柔力损衣，\n"
				+"初看完好无损，一经风吹，功力才露了出来。本因与本观、本相、本参、保定帝等互望见了几眼，都是暗暗惊异：\n"
				+"“凭咱们的功力，以一阳指虚点，破衣穿孔，原亦不难，但出指如此轻柔软，温颜微笑间神功已运，却非咱们所能。\n"
				+"这拈花指与一阳指全然不同，  其阴柔内力，确是颇有足以借镜之处。”\n"NOR,me);
	call_out("do_8",random(6),me);
	return 1;
}
int do_8(object me)
{
	tell_object(me,MAG"\n\n鸠摩智微笑道：“献丑了。小僧的拈花指指力，不及少林寺的玄渡大师远了。那‘多罗叶指’，只怕造诣更差。”当\n"
				+"下身形转动，绕着地下木箱快步而行，十指快速连点，但见木箱上木屑纷飞，不住跳动，顷刻间一只木箱已成为一片\n"
				+"片碎片。保定帝等见他指裂木箱，倒亦不奇，但见木箱的铰链、铜片、铁扣、搭钮等金属附件，俱在他指力下纷纷碎裂，\n"
				+"这才不由得心惊。\n"NOR);
	tell_object(me,HIG"\n\n鸠摩智笑道：“小僧使这多罗叶指，一味霸道，功夫浅陋得紧。”说着将双手拢在衣袖之中，突击之间，那一堆碎\n"
				+"木片忽然飞舞跳跃起来，便似有人以一要无形的细棒，不住去挑动搅拨一般。看鸠摩智时，他脸上始终带着温和笑\n"
				+"容，僧袖连下摆脱也不飘动半分，原来他指力从衣袖中暗暗发出，全无形迹。本相忍不住脱口赞道：“无相劫指，\n"
				+"名不虚传，佩服，佩服！”鸠摩智躬身道：“大师夸奖了。木片跃动，便是有相。当真要名副其实，练至无形无相，\n"
				+"纵穷毕生之功，也不易有成。”本相大师道：“慕容先生所遗奇书之中，可有破解‘无相劫指’的法门？”鸠摩智道：\n"
				+"“有的。破解之法，便从大师的法名上着想。”本相沉吟半晌，说道：“嗯，以本相破无相，高明之至。”\n"NOR);
	tell_object(me,HIR"\n\n鸠摩智却不站起，缓缓的道：“六脉神剑经既只徒具虚名，无裨实用，贵寺又何必如此重视？以致伤了天龙寺与大轮寺\n"
				+"的和气，伤了大理国和吐蕃国的邦交。”本因脸色微变，森严问道：“明王之言，是不是说：天龙寺倘若不允交经，大理、\n"
				+"吐蕃两国便要兵戎相见？”保定帝一向派遣重兵，驻扎西北边疆，以防吐蕃国入侵，听鸠摩智如此说，自是全神贯注的倾听。\n"
				+"鸠摩智道：“我吐蕃国主久慕大理国风土人情，早有与贵国国主会猎大理之念，只是小僧心想此举势必多伤人命，大违我佛\n"
				+"慈悲本怀，数年来一直竭力劝止。”\n"NOR);
	tell_object(me,HIY"\n\n枯荣大师道：“明王既坚要此经，老衲等又何敢吝惜？明王愿以少林寺七十二门绝技交换，敝寺不敢拜领。明王既已精通\n"
				+"少林七十二绝技，复又精擅大雪山大轮寺武功，料来当世已无敌手。”鸠摩智双手合什，道：“大师之意，是要小僧出手献丑？\n"
				+"”枯荣大师道：“明王言道，敝寺的六脉神剑经徒具虚名，不切实用。我们便以六脉神剑，领教明王几手高招。倘若确如明王所去，\n"
				+"这路剑法徒具虚名，不切实用，那又何足珍贵？明王尽管将剑经取去便了。”\n"NOR);
	call_out("do_start",random(6),me);

	return 1;
}

//开始战斗环节。。

int do_start(object me)
{
    
	tell_object(me,CYN"\n\n鸠摩智双手一击，门外走进一名高大汉子。鸠摩智说了几句番话，那汉子点头答应，到门外的箱子中取过一束藏香，交了给鸠摩智，\n"
				+"倒退着出门。众人都觉奇怪，心想这线香一触即断，难道竟能用作兵刃？只见他左手拈了一枝藏香，右手取过地下的一些木屑，\n"
				+"轻轻捏紧，将藏香插在木屑之中。如此一连插了六枝藏香，并成一列，每枝藏香间相距约一尺。鸠摩智盘膝坐在香后，隔着五尺左右，\n"
				+"突击双掌搓板了几搓，向外挥出，六根香头一亮，同时点燃了。众人都是大吃一惊，只觉这催力之强，实已到了不可思议的境界。\n"
				+"但各人随即闻到微微的硝磺之气，猜到这六枝藏香头上都有火药，鸠摩智并非以内力点香，乃是以内力磨擦火药，使之烧着香头。\n"
				+"这事虽然亦甚难能，但保定帝等自忖勉力也可办到。\n"NOR);
        call_out("do_start1",4,me);
		return 1;

}
int do_start1(object me)
{
        tell_object(me,HIG"\n\n\n\n藏香所生烟气作碧绿之色，六条笔直的绿线袅袅升起。鸠摩智双掌如抱圆球，内力运出，六道碧烟慢慢向外弯曲，分别指着\n"
				+"枯荣、本观、本相、本因、本参、保定帝六人。他这手掌力叫做‘火焰刀’，虽是虚无缥缈，不可捉摸，却能杀人于无瑚，实是\n"
				+"厉害不过。此番他只志在得经，不欲伤人，是以点了六枝线香，以展示掌柜力的去向形迹，一来显得有恃无恐，二来意示慈悲\n"
				+"为怀，只是较量武学修为，不求杀伤人命。\n"NOR);
		call_out("do_start2",4,me);
		return 1;

}
int do_start2(object me)
{
	tell_object(me,MAG"\n\n\n\n六条碧烟来到本因等身前三尺之处，便即停住不动。本因等都吃了一惊，心想以内力逼送碧烟并砂为难，但将这飘荡无定的\n"
				+"烟气弟在半空，那可难上十倍了。本参左手小指一伸，一条气流从少冲穴中激射线而出，指向身前的碧烟。那条烟柱受这道内力一逼，\n"
				+"迅速无比的向鸠摩智倒射线过去，射至他身前二尺时，鸠摩智的‘火焰刀’内力加盛，烟柱无法再向前行。鸠摩智点了点头，道：\n"
				+"“名不虚传，六脉神剑中果然有‘少泽剑’一路剑法。”两人的内力激荡数招，本参大师知道倘若若坐定不动，难以发挥剑法中的威力，\n"
				+"当即站起身来，向左斜行三步，左手小指的内力自左向右的斜攻过去。鸠摩智左掌一拨，登时挡住。\n"NOR);
    call_out("do_fight1",3,me);
    return 1;
}

int do_fight1()
{
	object me=this_player();
	object bencan,benguan,benxiang,benyin,kurong,benchen,jiumozhi;

	if (!objectp(bencan=present("bencan dashi",environment(me))))
	{
		bencan=new("d/tls/npc/ben-can");
		bencan->move(environment(me));
	}
	if (!objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		jiumozhi=new("kungfu/class/xueshan/jiumozhi");
		jiumozhi->move(environment(me));
		
	}
	    jiumozhi->add_temp("apply/armor",300);
		jiumozhi->add_temp("apply/parry",300);
		jiumozhi->add_temp("apply/defense",1000);
	if (!objectp(benguan=present("benguan dashi",environment(me))))
	{
		benguan=new("d/tls/npc/ben-guan");
		benguan->move(environment(me));
	}
	if (!objectp(benyin=present("benyin dashi",environment(me))))
	{
		benyin=new("d/tls/npc/ben-yin");
		benyin->move(environment(me));
	}
	if (!objectp(benxiang=present("benxiang dashi",environment(me))))
	{
		benxiang=new("d/tls/npc/ben-xiang");
		benxiang->move(environment(me));
	}
	if (!objectp(kurong=present("kurong u",environment(me))))
	{
		kurong=new("d/tls/npc/kurong");
		kurong->move(environment(me));
	}
	if (!objectp(benchen=present("duan zhengming",environment(me))))
	{
		benchen=new("d/dali/dlhg/npc/duanzm");
		benchen->move(environment(me));
	}
 
	call_out("do_fight2",5,me,jiumozhi,kurong);
	tell_object(me,HIY"本参大喝一声，请明王赐教！伸手一指，嗤嗤有声！\n"NOR);
	bencan->fight_ob(jiumozhi);   
	jiumozhi->fight_ob(bencan);
	
	
	tell_object(me,HIC"\n\n\n本观眼见二人剑气刀气纵横，鸠摩智看似游刃有余，于是喝道，”我来了“，说完伸手一指，一股劲气射出！\n"NOR);
	tell_object(me,HIR"\n鸠摩智喝道，”好，少冲剑，不错，不错！“\n"NOR);
	benguan->fight_ob(jiumozhi);   
	jiumozhi->fight_ob(benguan);
    tell_object(me,HIY"\n\n\n本因方丈见师兄师弟联手，占不到丝毫上风，心想我们练这剑法未熟，剑招易于用尽，六人越早出手越好，\n"
					+"这大轮明王聪明绝顶，眼下他显是在观察本观、本参二人的剑法，未以全力攻防，当即说道：“本相、本尘二位\n"
					+"师弟，咱们都是出手吧。”食指伸处，‘商阳剑法’展动，跟着本相的‘少冲剑’，保定帝的‘关冲剑’，三路剑气齐\n"
					+"向三条碧烟上击去。\n"NOR);
    tell_object(me,HIB"\n\n保定帝长叹一声，伸出一指，嗤嗤作响，正是【关冲剑】的招式！\n"NOR);
    benchen->fight_ob(jiumozhi);
	jiumozhi->fight_ob(benchen);
	
	tell_object(me,HIR"\n\n本因伸出一指，嗤嗤作响，正是【商阳剑】的招式！\n"NOR);
	benyin->fight_ob(jiumozhi);
	jiumozhi->fight_ob(benyin);
	tell_object(me,HIG"\n\n本相伸出一指，嗤嗤作响，正是【少冲剑】的招式！\n"NOR);
	benxiang->fight_ob(jiumozhi);
	jiumozhi->fight_ob(benxiang);
	
	tell_object(me,HIW"\n\n\n枯荣大师伸出手指写道，”良机莫失，凝神观剑。自观自学，不违祖训。“\n\n\n"NOR);
	message_vision(HIR"\n\n\n枯荣大师反过手来，双手拇指同时捺出，嗤嗤两声急响，分鸠摩智右胸左肩。他竟不挡敌人来侵，另遣两路\n"
						+"厅失急袭反攻。他料得鸠摩智的火焰刀内力上蓄势缓进，真要伤到自己，尚有片刻，倘若后发先至，当可打\n"
						+"个措手不及。\n"NOR);
	
	return 1;
	
}

int do_fight2 (object me,object jiumozhi,object kurong)
{
	
	tell_object(me,HIW"\n\n\n枯荣大师伸出手指写道，”良机莫失，凝神观剑。自观自学，不违祖训。“\n\n\n"NOR);
	tell_object(me,HIR"\n\n\n枯荣大师反过手来，双手拇指同时捺出，嗤嗤两声急响，分鸠摩智右胸左肩。他竟不挡敌人来侵，另遣两路\n"
						+"厅失急袭反攻。他料得鸠摩智的火焰刀内力上蓄势缓进，真要伤到自己，尚有片刻，倘若后发先至，当可打\n"
						+"个措手不及。\n"NOR);
		
	kurong->fight_ob(jiumozhi);
	jiumozhi->fight_ob(kurong);
	call_out("do_fight3",1,me,jiumozhi,kurong);
    return 1;

}
int do_fight3(object me,object jiumozhi,object kurong)
{
    
	//tell_object(me,HIR""NOR);
    if (kurong->is_fighting(jiumozhi)||jiumozhi->is_fighting())
    {
		call_out("do_fight3",3,me,jiumozhi,kurong);
		return 1;
    }
   
	tell_object(me,HIR"\n\n但见屋内烟雾渐淡渐薄，蒙蒙烟气之中，只见本因等五僧跪在地下，神情庄严，而本观与本参的眼色中\n"
					+"\n更是大显悲愤。鸠摩智一怔之下，登时省悟，暗叫：“不好！枯荣这老僧知道不敌，竟然将六脉神剑的图谱烧了。”\n"NOR);
	
	tell_object(me,HIC"、\n\n\n\n\n枯荣大师以一阳指的内力逼得六张图谱焚烧起火，生怕鸠摩智阻止抢夺，于是推动烟气向他进击，使他着力抵御，\n"
					+"待得烟气散尽，图谱已烧得干干净净。本因等均是精研一阳指的高手，一见黑烟，便知缘由，心想师叔宁为玉碎，\n"
					+"不肯瓦全，甘心将这镇寺之宝毁去，决不让之落入敌手。好在六人心中分别记得一咯剑法，待强敌退去，再行默写\n"
					+"出来便是，只不过祖传的图谱却终于就此毁了。\n"NOR);
	
	tell_object(me,HIG"\n\n\n鸠摩智又惊又怒，他素以智计自负，今日却接连两次败在枯荣大师的手下，六脉神剑红既已毁去，则此行徒\n"
						+"然结下个强仇，却是毫无收获。他站起身来，合什说道：“枯荣大师何必刚性乃尔？宁折不曲，颇见高致。\n"
						+"贵寺宝经因小僧而毁，心下大是过意不去，好在此经非一人之力所能练得，毁与不毁，原无多大分别。这就告辞。”\n"
						+"他微一转身，不待枯荣和本因对答，突然间伸手扣住了保定帝右手腕脉，说道：“敝国国主久仰保定帝风范，渴欲\n"
						+"一见，便请联合会下屈驾，赴吐蕃国一叙。”\n"NOR);
	//call_out("do_help",2,me,jiumozhi);
	//如果鸠摩智存在则能解救,若10秒钟解救不了，则鸠摩智逃跑
   // call_out("do_escape",20,me,jiumozhi);
	if (objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		
		tell_object(me,HIC"开始解救了。test。\n"NOR);     
	    add_action("do_jiejiu","jiejiu");
		me->start_busy(-1);
		me->set_temp("liumai/jiejiu",time());
	}
	return 1;
    
}

int do_jiejiu(string arg)
{
	object me=this_player();
	object jiumozhi;
    


	if (!arg || arg!="段正明")
	{
		message_vision("你要干嘛？\n",me);
		return 1;
	}
	if (time()-me->query("quest/tls/liumai_1/time")<86400)
    {
		message_vision("你方才不是刚解救过一次么，再来一次不累啊？\n",me);
		return 1;
		
    }

	message_vision(HIY"$N眼见保定帝被这蕃僧所制，心中大急，大喝一声冲了上去，和鸠摩智打斗在一起。试图解救保定帝出来。\n"NOR,me);
	if (!objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		jiumozhi=new("kungfu/class/xueshan/jiumozhi");
		jiumozhi->move(environment(me));		
	}
	jiumozhi->add_temp("apply/armor",300);
	jiumozhi->add_temp("apply/parry",300);
	jiumozhi->add_temp("apply/defense",1000);
	me->kill_ob(jiumozhi);
	jiumozhi->kill_ob(me);
	call_out("do_check",3,me,jiumozhi);
	
	return 1;

}


int do_check(object me,object jiumozhi)
{
    object kurong,benchen,benyin; 
	object ztzhu;
	if (!me)
	{
		message("channel:chat", HIC"【聊天】鸠摩智："+me->query("name")+"盛名之下，其实难符，不过如此，哼！\n"NOR, users());
		message("channel:chat", HIC"【聊天】鸠摩智：天龙寺好大的名头，也不过如此而已，哼！\n"NOR, users());
		message_vision(HIY"战斗结束，解密失败。\n"NOR,me);
		call_out("do_leave",2,me);
		return 1;

	}
	if (time()-me->query_temp("liumai/jiejiu")>20)
	{
		message_vision(HIY"鸠摩智猛然一阵，挣脱了你的纠缠，抓住保定帝，向外窜去!\n"
						+"\n\n战斗结束，解密失败。\n"NOR,me);
	    
		call_out("do_leave",2,me);
        return 1;
	}
	if (!living(jiumozhi)||!objectp(jiumozhi))
    {
		tell_object(me,HIR"鸠摩智有气无力地说道，天龙寺藏龙卧虎，果然有高手存在，哼，我大轮寺跟你没完。\n"NOR);
		tell_object(me,HIR"鸠摩智有气无力地说道，老子二十年后又是一条好汉。\n"NOR);

		message("channel:chat", HIC"【聊天】枯荣大师：哈哈哈哈哈！大轮明王不过如此而已，与大轮寺这梁子算是结下了！\n"NOR, users());
		message("channel:chat", HIC"【聊天】枯荣大师：我天龙寺乃天下第一名寺，六脉神剑必定名扬江湖！\n"NOR, users());
		message("channel:chat", HIC"【聊天】枯荣大师："+me->query("name")+"这娃娃不错，老夫看着顺眼！\n"NOR, users());

		tell_object(me,HIY"\n枯荣大师双手合十，低吟道，“阿弥陀佛”！然后转身对你说道，“不违背祖训，你到龙树苑来一次。”\n"NOR);
        if (objectp(kurong=present("kurong zhanglao",environment(me))))
	  		kurong->move("d/tls/lsy");
		
		tell_object(me,CYN"\n保定帝长叹一声，低吟道，“阿弥陀佛”！\n"NOR);
        if (objectp(benchen=present("duan zhengming",environment(me))))
	  		//benchen->move("d/dali/huanggong");
		destruct(benchen);
		
		tell_object(me,HIC"\n其他诸位大师也是感慨万千，不由地随着枯荣大师的离去而喟然一叹！\n"NOR,me);
		
		destruct(present("benyin dashi",environment(me)));
		
		me->set_temp("liumai/fightzhiok",1);
		//解密结束，取消busy，防止多人解密导致的混乱
		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
        return 1;
    }
	
	if (jiumozhi->query("qi")<jiumozhi->query("max_qi")/2 
		&& jiumozhi->is_fighting(me))
    {
		tell_object(me,HIR"鸠摩智冷哼一声，说道，天龙寺藏龙卧虎，果然有高手存在，哼，后会有期！说完后，向外跃去。\n"NOR);
		destruct(jiumozhi);
		message("channel:chat", HIC"【聊天】鸠摩智："+me->query("name")+"你给我等着，我大轮寺跟你没完！\n"NOR, users());
		message("channel:chat", HIC"【聊天】枯荣大师：哈哈哈哈哈！大轮明王一路走好！\n"NOR, users());
		message("channel:chat", HIC"【聊天】枯荣大师：我天龙寺乃天下第一名寺，六脉神剑必定名扬江湖！\n"NOR, users());
		message("channel:chat", HIC"【聊天】枯荣大师："+me->query("name")+"这娃娃不错，老夫看着顺眼！\n"NOR, users());

		tell_object(me,HIY"\n枯荣大师双手合十，低吟道，“阿弥陀佛”！然后转身对你说道，“不违背祖训，你到龙树苑来一次。”\n"NOR);
        if (objectp(kurong=present("kurong zhanglao",environment(me))))
	  		kurong->move("d/tls/lsy");
		
		tell_object(me,CYN"\n保定帝长叹一声，低吟道，“阿弥陀佛”！\n"NOR);
        if (objectp(benchen=present("duan zhengming",environment(me))))
			destruct(benchen);
		
		tell_object(me,HIC"\n其他诸位大师也是感慨万千，不由地随着枯荣大师的离去而喟然一叹！\n"NOR,me);
		
		destruct(present("benyin dashi",environment(me)));
		//成功标记
		me->set_temp("liumai/fightzhiok",1);
		me->set("quest/tls/liumai/winzhi",1);
		//解密结束，取消busy，防止多人解密导致的混乱
		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
        return 1;
    }
	
	if (jiumozhi->is_fighting(me))
	{
		remove_call_out("do_check");
		call_out("do_check",1,me,jiumozhi);
		return 1;
	}

}

int do_leave(object me)
{
	object kurong,jiumozhi,benyin,dzm;
	object ztzhu;
	if (objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		message("channel:chat", HIC"【聊天】鸠摩智："+me->query("name")+"盛名之下，其实难符，不过一具酒囊饭袋，哼！\n"NOR, users());
		message("channel:chat", HIC"【聊天】鸠摩智：天龙寺好大的名头，也不过如此而已，哼！\n"NOR, users());
		destruct(jiumozhi);			
		

	}
	if (objectp(benyin=present("benyin dashi",environment(me))))
	{
		tell_object(this_object(),HIY"本因大师喟然一叹，唉，想不到天龙寺竟然面临如此灾难！我这掌门有愧啊。\n"NOR);
		destruct(benyin);

	}
	if (objectp(kurong=present("kurong zhanglao",environment(me))))
	{
		tell_object(this_object(),HIY"枯荣大师喟然一叹，唉，想不到天龙寺竟然面临如此灾难！\n"NOR);

		destruct(kurong);

	}
	if (objectp(dzm=present("duan zhengming",environment(me))))
	{
		destruct(dzm);

	}
   if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
	me->add("quest/tls/liumai_1/fail",1);
    me->set("quest/tls/liumai_1/time",time());

	return 1;

}
