//cre by sohu@xojh 2014
//monitang.h 火焰刀 vs 六脉神剑

#include <ansi.h>



int do_baijian(string arg)
{
	object me = this_player();
   
	if( !me->query_temp("hydjj/receive"))
		return notify_fail("这里是天龙寺牟尼堂，你要干什么？\n");
    if (!arg)
		return notify_fail("你要干什么？\n");
	if (arg=="枯荣长老"||arg=="枯荣大师"||arg=="枯荣禅师")
	{
		tell_object(me,HIC"\n\n你朗声说道，”大轮寺首座鸠摩智座下弟子“"+me->query("name")+"前来拜见枯荣大师。\n"NOR);
		tell_object(me,HIY"\n\n枯荣大师说道，”你那拜帖我也都见了，你来此有何贵干？”\n"NOR);
	    call_out("bai_1",random(5),me);
	}
	return 1;
}

int bai_1(object me)
{
	
	message_vision(HIR"\n\n$N缓缓的道：“六脉神剑经既只徒具虚名，无裨实用，贵寺又何必如此重视？以致伤了天龙寺与大轮寺\n"
				+"的和气，伤了大理国和吐蕃国的邦交。”本因脸色微变，森严问道：“$N之言，是不是说：天龙寺倘若不允交经，大理、\n"
				+"吐蕃两国便要兵戎相见？”保定帝一向派遣重兵，驻扎西北边疆，以防吐蕃国入侵，听$N如此说，自是全神贯注的倾听。\n"
				+"$N道：“我吐蕃国主久慕大理国风土人情，早有与贵国国主会猎大理之念，只是小僧心想此举势必多伤人命，大违我佛\n"
				+"慈悲本怀，数年来一直竭力劝止。”\n"NOR,me);
	message_vision(HIY"\n\n枯荣大师道：“$N既坚要此经，老衲等又何敢吝惜？$N愿以少林寺七十二门绝技交换，敝寺不敢拜领。$N既已精通\n"
				+"少林绝技，复又精擅大雪山大轮寺武功，料来当世已无敌手。”$N双手合什，道：“大师之意，是要小僧出手献丑？\n"
				+"”枯荣大师道：“$N言道，敝寺的六脉神剑经徒具虚名，不切实用。我们便以六脉神剑，领教$N几手高招。倘若确如$N所说，\n"
				+"这路剑法徒具虚名，不切实用，那又何足珍贵？$N尽管将剑经取去便了。”\n"NOR,me);
	message_vision(CYN"\n\n\n\n枯荣大师说道，既然大师如此说，那就"HIR"“斗剑(doujian)”"CYN"定输赢，伸手对$N示意，大师请！\n\n\n\n"NOR,me);
	me->delete_temp("hydjj/receive");
	me->set_temp("hydjj/baijian",1);
	add_action("do_bijian","doujian");
	return 1;
}

int do_bijian()
{
	object me,kurong,bencan,benguan,benxiang,benchen,benyin;
	me=this_player();
	//消掉第一个标记
    me->delete_temp("hydjj/receive");
	
    if (!me->query_temp("hydjj/baijian"))
    {
		return notify_fail("你要自己斗剑？\n");
    }
	if (me->query_skill_mapped("strike")!="huoyan-dao"
		||me->query_skill_prepared("strike")!="huoyan-dao"
		||me->query_skill_mapped("parry")!="huoyan-dao")
    {
		message_vision("你激发的武技不是火焰刀？\n",me);
		return 1;
    }
	
	if (time()-me->query("quest/dls/hyd/time")<86400)
    {
		message_vision("你方才不是斗过剑么，再来一次不累啊？\n",me);
		return 1;
		
    }
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
	if (me->query("combat_exp")>15000000)
	{
		
		call_out("super_ben",1,me,bencan);
		call_out("super_ben",1,me,benguan);
		call_out("super_ben",1,me,benxiang);
		call_out("super_ben",1,me,benyin);
		call_out("super_ben",1,me,benchen);
		call_out("super_ben",1,me,kurong);
	}
	

    bencan->fight_ob(me);
	me->fight_ob(bencan);
	benguan->fight_ob(me);
	me->fight_ob(benguan);
	benxiang->fight_ob(me);
	me->fight_ob(benxiang);
	benyin->fight_ob(me);
	me->fight_ob(benyin);
	benchen->fight_ob(me);
	
	me->fight_ob(benchen);
	kurong->kill_ob(me);
	me->kill_ob(kurong);
    me->delete_temp("hydjj/baijian");
    
	me->set_temp("hydjj/fighttls",1);
	//标记临时时间变量
	me->set("quest/dls/hyd/temptime",time());
	
	call_out("check_hyd",1,me,bencan,benguan,benxiang,benyin,benchen,kurong);
	return 1;

}
int check_hyd(object me,object bencan,object benguan,object benxiang,object benyin,object benchen,object kurong)
{
	
	//设定临时时间，60秒内杀不死枯荣，则会焚烧六脉剑谱
	int t;
	object book,ztzhu;
	t=time()-me->query("quest/dls/hyd/temptime");

	if (!living(me)||!me
		||!me->query_temp("hydjj/fighttls")
		||(t>60 && objectp(kurong))
		||me->query("qi")<me->query("max_qi")/3)
	{
		message_vision(HIG"\n\n$N忽然间感觉屋内烟雾缭绕，而众僧俱都面带凄惨之相，心中顿时恍悟！\n"NOR,me);
		message_vision(HIY"\n\n这枯荣大师眼见抵挡不过，竟然将这天龙寺镇寺之宝的六脉神剑剑谱以内力烧掉！\n"NOR,me);
		message_vision(HIC"\n\n$N不由滴心中大怒！但却无可奈何。\n"NOR,me);
		tell_object(me,HIW"\n\n解密火焰刀碧烟纵横战斗失败！\n"NOR);
		me->add("quest/dls/hyd/fail",1);
		me->set("quest/dls/hyd/time",time());
		//logfile
		message("channel:chat", HIC"【聊天】枯荣长老："+me->query("name")+HIC"好大的胆子，居然敢到天龙寺来撒野！\n"NOR, users());
		message("channel:chat", HIC"【聊天】枯荣长老：大轮寺大轮明王鸠摩智好大的名头，门下弟子也不过如此而已！\n"NOR, users());
		message("channel:rumor", HIM"【谣言】某人："+me->query("name")+HIM"企图抢夺天龙寺镇寺之宝六脉神剑谱失败！\n"NOR, users());

		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
		return 1;


	}
	if ( !objectp(kurong)||!living(kurong)|| (t<60 && kurong->query("qi")< kurong->query("max_qi")/2))
	{
		message_vision(HIG"\n\n$N战斗甚是轻松，眼角瞄见枯荣大师偷偷地从怀中掏出一本古书！\n"NOR,me);
		message_vision(HIY"\n\n$N心中恍然大悟，知道那就是传说中六脉神剑剑谱，枯荣大师意图正欲将此剑谱烧毁！\n"NOR,me);
		message_vision(HIC"\n\n$N眼疾手快，战斗之余，控制火焰刀一记手刀绝技斩向枯荣大师的手腕！\n"NOR,me);
		message_vision(HIR"\n\n枯荣大师惨叫一声，六脉神剑图谱掉落在地！\n"NOR,me);
        
		message("channel:rumor", HIM"【谣言】某人："+me->query("name")+HIM"成功抢夺天龙寺镇寺之宝六脉神剑谱！\n"NOR, users());
		
		
		book=new("/d/tls/npc/obj/jianpu");
		book->set("owner",me->query("id"));
		book->move(environment(me));
		//message_vision(HIR"\n\n枯荣大师惨叫一声，六脉神剑图谱掉落在地！\n"NOR,me);
		//掉落剑谱
		if (living(bencan))
		{
			bencan->kill_ob(me);
			me->kill_ob(bencan);
		}
		if (living(benguan))
		{
			benguan->kill_ob(me);
			me->kill_ob(benguan);
		}
		if (living(benyin))
		{
			benyin->kill_ob(me);
			me->kill_ob(bencan);
		}
		if (living(benxiang))
		{
			benxiang->kill_ob(me);
			me->kill_ob(benxiang);
		}
		if (living(benchen))
		{
			benchen->kill_ob(me);
			me->kill_ob(benchen);
		}
		if (living(kurong))
		{
			kurong->kill_ob(me);
			me->kill_ob(kurong);
		}
		me->set_temp("hydjj/tlsover",1);
		me->delete_temp("hydjj/fighttls");
		
		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
		return 1;
	}
	call_out("check_hyd",1,me,bencan,benguan,benxiang,benyin,benchen,kurong);
	return 1;

}