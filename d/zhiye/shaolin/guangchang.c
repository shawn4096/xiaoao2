// Room: /d/shaolin/guangchang1.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

int init();
int do_open();
int xiao_ding1(object me);
int xiao_ding2(object me);
int xiao_ding3(object me);
int xiao_ding4(object me);
string look_gate();
#define QUESTDIR3 "quest/ÌìÁú°Ë²¿/Ïô·åÉíÊÀÆª/"
#define QUESTDIR5 "quest/ÌìÁú°Ë²¿/¸´ÐËÌìÏÂÆª/"

void create()
{
	set("short", "¹ã³¡");
	set("long", @LONG
ÕâÀïÊÇÉÙÁÖËÂÇ°µÄ¹ã³¡£¬Õû¸ö¹ã³¡ÓÉ´ó¿éµÄÇàÊ¯ÆÌ³É£¬¼«ÎªÆ½Ì¹¡£µ«ÒòÄê
´ú¾ÃÔ¶£¬¶¼ÓÐÐ©ÆÆËð¡£´Ô´ÔÐ¡²Ý´ÓÊ¯°åµÄ·ìÏ¶ÖÐ³¤ÁË³öÀ´¡£¹ã³¡ÖÜÎ§¶¼ÊÇÃÜÃÜ
µÄËÉÊ÷ÁÖ£¬ËÄ½ÇÉÏ¸÷·ÅÁË¼¸¿éÊ¯±®£¬×Ö¼£¶¼ÉõÎªÄ£ºý¡£ÕýÇ°·½»ÆÇ½±ÌÍß£¬·ÉéÜ
ÇÌéÝ£¬ÕýÖÐÒ»µÀ¶þÕÉÀ´¿í£¬ÈýÕÉÀ´¸ßµÄÖìºìÉ¼Ä¾°üÍ­´óÃÅ(gate)¡£ÉÏ·½Ò»¿é´ó
ØÒ£¬Áú·É·ïÎèµØÊé×Å¡º[1;33mÉÙÁÖËÂ[0;37;0m¡»Èý¸ö´ó×Ö¡£ËÂÇ°ÈýÈýÁ½Á½µÄÕ¾×Å¼¸¸öÉ®ÈË¡£
LONG
    );

	set("exits", ([
		"east" : __DIR__"gchange",
		"south" : __DIR__"shifang",
		"west" : __DIR__"gchangw",
	]));

	set("outdoors", "shaolin");
	set("item_desc",([
		"gate"        :    (: look_gate :),
	]));

	set("objects",([
		CLASS_D("shaolin") + "/qing-fa" : 1,
	]));

	setup();
	"/clone/board/shaolin_b"->foo();
}

int init()
{
  object me;
 
  me = this_player();
  if(!me->query_condition("killer") && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"dagouzhen"))
  {
   tell_object(me,HIC"\nÄã×ÜËã×ß³öÉÙÁÖËÂ£¬À´µ½É½ÃÅµî¹ã³¡¡£Í»È»ÄãÓÖÓÐÒ»ÖÖ²»ÃîµÄÔ¤¸Ð¡£\n"NOR); 
   message_vision(WHT"É½ÏÂ´Ò´Ò×ßÀ´Ò»¸öÈË£¬Ïò$NÒ»¹°ÊÖµÀ£º¡°ºÙºÙ£¬Ê©Ö÷Èç´ËÐ×ºÝ£¬»¹ÊÇÁôÔÚÉÙÁÖÇ±ÐÞ·ð·¨µÃºÃ°¢¡£¡±\n"NOR,me);
   me->move("/d/gb/dagouzhen");
   tell_object(me,HIR"ÄãÒÉ»óÁËÒ»ÏÂ£¬È´·¢ÏÖËÄÖÜÎ§ÉÏÒ»È¦ÈË£¬ËÆºõÊÇØ¤°ï´ò¹·Õó·¨¡£\n"NOR);
   log_file("quest/TLBB", sprintf("%s(%s)±»¹Ø½ø´ò¹·Õó¡£¾­Ñé£º%d¡£\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return 1;
  }
	add_action("do_knock", "knock");
   //Ôö¼ÓÏô·å´óÕ½¶¡´ºÇïÇé½Ú
   if (me->query_temp("xlz/askxiao1"))
   {
	   //me->delete_temp("xlz/askxiao1");
	   if (!present("ding chunqiu",environment(me)))
	   {
		   new("/d/xingxiu/npc/ding.c")->move("/d/shaolin/guangchang");
		}
       if (!present("xuanci dashi",environment(me)))
	   {
		   new("/kungfu/class/shaolin/xuan-ci.c")->move("/d/shaolin/guangchang");
		}
	  if (!present("xingxiu dizi",environment(me)))
      {
	   new("/d/xingxiu/npc/xxdizi.c")->move("/d/shaolin/guangchang");
       }
	  //me->start_busy(3);
	  call_out("xiao_ding1",2,me);
	  //me->delete_temp("xlz/askxiao1");
	 // return 1;
   }

}

int close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");
	if(objectp(room)) {
	delete("exits/north");
	message("vision", "Æ¹µØÒ»Éù£¬ÀïÃæÓÐÈË°Ñ´óÃÅ¹ØÉÏÁË¡£\n", this_object());
	room->delete("exits/south");
	if (objectp(present("qingfa biqiu", room)))
		message("vision", "Çå·¨±ÈÇðÉÏÇ°°Ñ´óÃÅ¹ØÁËÆðÀ´¡£\n", room);
	else
		message("vision", "×³ÄêÉ®ÈËÉÏÇ°°Ñ´óÃÅ¹ØÁËÆðÀ´¡£\n", room);
	}
	else message("vision", "ERROR: gate not found(close).\n", room);
}

int do_knock(string arg)
{
	object room;

	if (query("exits/north"))
		return notify_fail("´óÃÅÒÑ¾­ÊÇ¿ª×ÅÁË¡£\n");

	if (!arg || (arg != "gate" && arg != "north"))
		return notify_fail("ÄãÒªÇÃÊ²Ã´£¿\n");

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");

	if(objectp(room)) {
		set("exits/north", __DIR__"smdian");
		message_vision("$NÇáÇáµØÇÃÁËÇÃÃÅ£¬Ö»ÌýÖ¨µØÒ»Éù£¬Ò»Î»×³ÄêÉ®ÈËÓ¦Éù´ò¿ª´óÃÅ£¬\n"
				"ËûÓÃÈñÀûµÄÄ¿¹âÉÏÉÏÏÂÏÂ´òÁ¿×Å$N¡£\n",this_player());
		room->set("exits/south", __FILE__);
		message("vision", "ÍâÃæ´«À´Ò»ÕóÇÃÃÅÉù£¬×³ÄêÉ®ÈËÓ¦ÉùÉÏÇ°°Ñ´óÃÅ¿ª¡£\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("xlz/askxiao1"))
	{
		notify_fail("Äã»¹ÓÐ¾çÇéÃ»Íê³É,²»ÄÜÀë¿ª£¡\n");
		return;
	}
	
	if ( dir != "north" )
	return ::valid_leave(me, dir);

	if (is_wanted(me))
		return 0;
	if ( me->query("family/family_name") == "ÉÙÁÖÅÉ" ) {
		if ( me->query("guilty") == 0
		 && me->query("K_record") == ( me->query("PKS") + me->query("MKS"))) {
			message_vision("×³ÄêÉ®ÈË²àÉíÈÃ¿ª£¬ËµµÀ£ºÊ¦ÐÖÐÁ¿àÁË£¬Çë½ø¡£\n", me);
			return 1;
		}
		else {
			if((int)me->query("guilty") == 0) {
				int shen = me->query("shen");
				if((int)me->query("shen_record") > shen)
					me->set("guilty", 1);
				else
					me->set("guilty", 2);
				me->set("K_record", me->query("PKS") + me->query("MKS"));
				if (shen > 0 && shen > me->query("combat_exp")) shen = me->query("combat_exp");
				if (shen < 0 && -shen > me->query("combat_exp")) shen = -me->query("combat_exp");
				if (shen < 0) shen += shen / 9;
				else shen -= shen / 9;
				me->set("shen_record", shen);
			}
			write("×³ÄêÉ®ÈË³ÁÏÂÁ³À´£¬ËµµÀ£º½äÂÉÔºÖ÷³ÖÐþ¼Å´óÊ¦ÇëÊ¦ÐÖ»ðËÙÈ¥½äÂÉÔº³ÂÊö´ËÐÐ¹ý·¸¡£\n");
			return 1;
		}
	}
	else if( present("yingxiong ling", me)){
		message_vision("×³ÄêÉ®ÈËºÏÊ®ÎªÀñ£¬²àÉíÈÃ¿ª£¬ËµµÀ£ºÔ­À´ÊÇ¹ó¿Í¼Ýµ½£¬Çë½øÇë½ø£¡\n", me);
		return 1;
	}
	else if (me->query("luohan_winner")) {
		message_vision(HIY "×³ÄêÉ®ÈË¶Ô$NºÏÊ®ÎªÀñ£¬²àÉíÈÃ¿ª£¬ËµµÀ£ºÔ­À´ÊÇ´³¹ýÂÞººÕóµÄ´óÓ¢ÐÛ¼Ýµ½£¬Çë½øÇë½ø£¡\n" NOR, me);
		return 1;
	}
	if (me->query("shen") >= 0) {
		if (me->query("gender") == "Å®ÐÔ") {
			return notify_fail("×³ÄêÉ®ÈËËµµÀ£ºÕâÎ»Å®Ê©Ö÷»¹ÊÇÇë»Ø°Õ£¬±¾ËÂ´Ó²»½Ó´ýÅ®¿Í¡£\n");
		}
		else {
			return notify_fail("×³ÄêÉ®ÈËËµµÀ£ºÕâÎ»Ê©Ö÷Çë»Ø°Õ£¬±¾ËÂ²»½Ó´ýË×ÈË¡£\n");
		}
	}
	return notify_fail("×³ÄêÉ®ÈËÁ¢Ê±´ÓÉíÅÏÖ¿³öÒ»°ÑÑ©ÁÁµÄ½äµ¶À´£¬°ÑÃ÷»Î»ÎµÄ\n"
			"µ¶¼â¶Ô×¼ÄãµÄÐØ¿Ú£¬ºáÃ¼Å­Ä¿µØËµµÀ£ºÄãµÈÐ°Ä§ÍâµÀ£¬»¹²»¸øÎÒ¹ö¿ª£¡\n"
			"ÒÔºóÔÙ¸Ò×ß½üÉÙÁÖÒ»²½£¬ÎÒÁ¢Ê±¾ÍÕ¶¶ÏÄãÃÇµÄ¹·ÍÈ£¡\n");

	if(me->query("no_quest"))
		return notify_fail("\n");
}

string look_gate()
{
	return "Ò»µÀÈýÕÉÀ´¸ßµÄÖìºìÉ¼Ä¾°üÍ­´óÃÅ¡£\n";
}


int xiao_ding1(object me)
{
 
   message_vision(CYN"\nÀÏñÄµ±ÒÔ±¾ÅÉ´ó½ð¸ÕÕÆ½ÓÒ»½Ó°ïÖ÷µÄ½µÁúÊ®°ËÕÆ£¬ÒÔ½µÄ§ìøÕÌ½ÓÒ»½Ó°ïÖ÷µÄ´ò¹·°ô¡£°¦£¬\n"
                      +"ÉÙÁÖÅÉºÍ¹óÅÉÊÀ´ú½»ºÃ£¬Õâ¼¸ÖÖÎä¹¦£¬ÏòÀ´ÇÐ´è×ÁÄ¥ÔòÓÐÖ®£¬´ÓÀ´Ã»ÓÐÓÃÒÔµÐ¶Ô¹ýÕÐ£¬\n"
					  +"ÀÏñÄ²»µÂ£¬È´ÊÇÀ¢¶ÔØ¤°ïÀú´ú°ïÖ÷ºÍÉÙÁÖÅÉÀú´úÕÆÃÅÁË¡£\n"NOR,me);
   message_vision(HIB"\n¶¡´ºÇïºÃÏñÉõÊÇÉúÆø£¬ÈÌ²»×¡ºßÁËÒ»Éù£¬½«Í·¿´ÁËÉíÅÔµÄ°¢×ÏÒ»ÑÛ£¬ÉîÇéÉõÊÇ¸´ÔÓ£¬\n" NOR,me);
   message_vision(HIG"\nÐÇËÞÅÉÉñ¹¦±ÈØ¤°ï½µÁúÊ®°ËÕÆÇ¿µÃ¶à£¬¸ÉÃ´²»Ê¹Ç¿µÄ£¬·´Ê¹²î¾¢µÄ£¿\n"NOR,me);
   message_vision(HIG"\n×¯Ê¦ÐÖ£¬ÔÙÉÏ£¡µ±È»ÒªÓÃ¶÷Ê¦ÐÇËÞÀÏÏÉ´«¸øÄãµÄÉñ¹¦£¬È¥Ô×ÁËÀÏºÍÉÐ£¡\n"NOR,me);  
   message_vision(HIG"\nÐÇËÞµÜ×Ó·×·×ËµµÀ£º¡°ÐÇËÞÉñ¹¦£¬ÌìÏÂµÚÒ»£¬Õ½ÎÞ²»Ê¤£¬¹¥ÎÞ²»¿Ë¡£½µÁú³ôÕÆ£¬¹·Æ¨²»Öµ£¡¡±\n",me);
   message_vision(HIC"\n\nÐÇËÞµÜ×Ó·×·×ËµµÀ£º¡°ÐÇËÞÉñ¹¦£¬ÌìÏÂµÚÒ»£¬Õ½ÎÞ²»Ê¤£¬¹¥ÎÞ²»¿Ë¡£½µÁú³ôÕÆ£¬¹·Æ¨²»Öµ£¡¡±\n",me);
   message_vision(HIB"\n\nÐÇËÞµÜ×Ó·×·×ËµµÀ£º¡°ÐÇËÞÉñ¹¦£¬ÌìÏÂµÚÒ»£¬Õ½ÎÞ²»Ê¤£¬¹¥ÎÞ²»¿Ë¡£½µÁú³ôÕÆ£¬¹·Æ¨²»Öµ£¡¡±\n",me);
   message_vision(HIY"\n\nÐÇËÞµÜ×Ó·×·×ËµµÀ£º¡°ÐÇËÞÉñ¹¦£¬ÌìÏÂµÚÒ»£¬Õ½ÎÞ²»Ê¤£¬¹¥ÎÞ²»¿Ë¡£½µÁú³ôÕÆ£¬¹·Æ¨²»Öµ£¡¡±\n",me);
   
   me->delete_temp("xlz/askxiao1");
   call_out("xiao_ding2",5,me);

   return 1;

}

int xiao_ding2(object me)
{
  
   message_vision(HIC"\n\n\nÒ»Æ¬Ðú»©½ÐÈÂÖ®ÖÐ£¬ºöÌýµÃÉ½ÏÂÒ»¸öÐÛ×³µÄÉùÒôËµµÀ£º¡°Ë­ËµÐÇËÞÅÉÎä¹¦Ê¤µÃÁËØ¤°ïµÄ½µÁúÊ®°ËÕÆ£¿¡±\n"NOR,me);
   call_out("xiao_ding3",5,me);
   return 1;

}
int xiao_ding3(object me)
{
  object ding,xf,xuan;
  //xuan=present("xuan ci",environment(me));
   
  if (!objectp(present("ding chunqiu",environment(me))))
  {
     new("/d/xingxiu/npc/ding.c")->move("/d/shaolin/guangchang");
  }
  ding=present("ding chunqiu",environment(me));

  // xx1=present("xingxiu dizi",environment(me));
   message_vision(HIY"\nÕâÉùÒôÒ²²»Èç´ËÏìÁÁ£¬µ«ÇåÇå³þ³þµÄ´«ÈëÁË´ÓÈË¶úÖÐ£¬ÖÚÈËÒ»ãµÖ®¼ä£¬¶¼×¡ÁË¿Ú¡£\n"NOR,me);
   message_vision(CYN"\n\nµ«ÌýµÃÌãÉùÈçÀ×£¬Ê®Óà³ËÂí¼²·ç°ã¾íÉÏÉ½À´¡£ÂíÉÏ³Ë¿ÍÒ»É«¶¼ÊÇÐþÉ«±¡Õ±´óë©£¬ÀïÃæÐþÉ«²¼ÒÂ£¬\n"
                      +"µ«¼ûÈËËÆ»¢£¬ÂíÈçÁú£¬ÈË¼È½Ã½Ý£¬ÂíÒàÐÛ¿¥£¬Ã¿Ò»Æ¥Âí¶¼ÊÇ¸ßÍ·³¤ÍÈ£¬Í¨ÌåºÚÃ«£¬±¼µ½½ü´¦£¬\n"
					  +"ÈºÐÛÑÛÇ°Ò»ÁÁ£¬½ð¹âÉÁÉÁ£¬È´¼ûÃ¿Æ¥ÂíµÄÌãÌú¾¹È»ÊÇ»Æ½ð´ò¾Í¡£À´ÕßÒ»¹²ÊÇÒ»Ê®¾ÅÆï£¬ÈËÊýËä²»Éõ¶à£¬\n"
					  +"ÆøÊÆÖ®×³£¬È´ËÆÓÐÈçÇ§¾üÍòÂíÒ»°ã£¬Ç°ÃæÒ»Ê®°ËÆï±¼µ½½ü´¦£¬À­ÂíÏòÁ½ÅÔÒ»·Ö£¬×îºóÒ»Æï´ÓÖÐ³Û³ö¡£\n"
					  +"Ø¤°ï°ïÖÚÖ®ÖÐ£¬´óÈºÈËÃÍµØ¸ßÉùºô½Ð£º¡°ÇÇ°ïÖ÷£¬ÇÇ°ïÖ÷£¡¡±Êý°ÙÃû°ïÖÚ´ÓÈË´ÔÖÐ¼²±¼³öÀ´£¬ÔÚÄÇÈËÂíÇ°¹ªÉí²Î¼û¡£\n"NOR,me);
  if (!present("xiao feng",environment(me)))
  {
	  xf=new("/d/nanyang/npc/xiaofeng.c");
      xf->move(this_object());
	 /* xf->delete("chat_msg_combat");
	  xf->set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: perform_action, "strike.sanzhang" :),
			  }));*/
	  message_vision(HIR"\n\nÏô·å¿ì²½×ßÁË¹ýÀ´£¬²½Èëµ±³¡£¬Ó¢ÐÛÆøÊÆÁÝÈ»,¿´Ïò¶¡´ºÇïºÈµÀ£¬¡°¿´ÕÆ£¡¡±¡£\n"NOR,me);
  }
  ding->kill_ob(xf);
  ding->kill_ob(me);
  //¶¡Èô±»´òÔÎ

 
  call_out("xiao_ding4",30,me);
  //me->set_temp("xiaovsding",1);
  return 1; 
}

int xiao_ding4(object me)
{
    
	int i,j,g,t;
	object ding,xiao,xuanci,xxdizi;
	ding=present("ding chunqiu",environment(me));
	xiao=present("xiao feng",environment(me));
	xuanci=present("xuanci dashi",environment(me));
    xxdizi=present("xingxiu dizi",environment(me));
    if(file_name(environment(me))!="/d/shaolin/guangchang" ){
		message_vision(HIY"ÒòÎªÄãÒÑ¾­Àë¿ªÉÙÁÖ¹ã³¡£¬¶ÔÓÚ¹ã³¡Ëù·¢ÉúµÄÊÂÇéÒ»ÎÞËùÖª¡£\n"NOR,me);
        me->add("xlz/sanzhao/fail",1);
		me->set("xlz/sanzhao/time",time());
		me->delete_temp("xlz/askxiao1");
        return 1;
	}
	/*if (!objectp(ding))
	{
		mesage_vision(HIC"Ïô·åÁ¬ÐøÔËÊ¹½µÁúÊ®°ËÕÆµÄ¿ºÁúÓÐ»Ú¾ø¼¼£¬ÈýÕÐÖ®ºó½«¶¡´ºÇï´òµ½ÔÚµØ¡£\n"NOR,me);
	    mesage_vision(HIY"Ò»ÈºÉÙÁÖµÜ×ÓÉÁÁË³öÀ´£¬½«¶¡´ºÇïÑºÁËÏÂÈ¥¡£Ò»Ê±¼ä¹ã³¡ÉÏ±äµÃÀäÀäÇåÇå¡£\n"NOR,me);
		//destruct(dcq);
		//destruct();
     }*/
	message_vision(CYN"\n\nÄã´ô´ôµÄ¿´×ÅÑÛÇ°ÕâÒ»Ä»£¬¾¡¹ÜÄãÒÑ¾­ÁìÎòÁËÈ«²¿µÄ½µÁúÊ®°ËÕÆ£¬µ«ÕâÈýÕÐ´ÓÏô·çÊÖÖÐÊ©Õ¹³öÀ´¡£\n"NOR, me);
	message_vision(CYN"\È´ÍðÈçÁçÑò¹Ò½Ç£¬ÎÞ¼£¿ÉÑ°£¬È´ÓÖËÆÒ»ÕóµçÉÁÀ×Ãù£¬ÔÚÄãµÄÄÔº£ÖÐ¼¤ÆðÇ§ÍòÕÉµÄ²¨ÌÎÐÚÓ¿¡£\n"
			           +"ÕâÐ©ÕÐÊ½¶ÔÄãÀ´ËµÄãÒÑ¾­ÁËÈ»ÈôÐØ£¬Ò»Ê±Ö®¼ä¾¹È»´ôÁ¢µ±³¡..........................\n"
					   +"..............................................................................\n"NOR,me);

	j=random(me->query("kar"));
	g=random(me->query("relife/gifts/total"));
	//¸»Ô´£¬Ëæ»ú²ÎÎò>=15µã£¬ÇÒ±ÛÁ¦>45
	t=20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	i= random(t);
	
	if (me->query("kar")<31
		&& j>26
		&& i<3
		&& random(g)>=15
		&& random(me->query("str"))>40)
	{
       message_vision(HIC"$N»ÐÈ»´óÎò£¬Õâ½µÁúÕÆÒªÏëÁ·³É¾ø·ÇÒ»ÈÕÖ®¹¦£¬¶ÔÓÚ±ÛÁ¦ÒªÇóÊÇºÜ¸ßµÄ¡£\n"NOR,me);
	   message_vision(HIC"$NÍ¬Ê±ÈÚ»á¹áÍ¨ºÍÊìÄÜÉúÇÉÒ²ÊÇÎä¼¼´ïµ½áÛ·åµÄ±ØÓÉÖ®Â·£¬Ô­À´Õâ¾ÍÊÇ·µè±¹éÕæµÄµÀÀí¡£\n"NOR,me);
	   message_vision(HIC"$N¹§Ï²Äã£¬Àú¾­Ç§ÄÑÍòÏÕ£¬ÖÕÓÚÁìÎòÏô·åËù´«µÄÈýÕÐÁ¬»·½µÁúÕÆ¾ø¼¼¡£\n"NOR,me);
	   xiao->command("chat* haha"+me->query("id"));
	   
	   xiao->command("chat "+"Ø¤°ï½µÁúÊ®°ËÕÆÄËÊÇÎäÁÖÖÐ×î°ÔµÀµÄÕÆ·¨¡£");
	   xiao->command("chat* admire"+me->query("id"));
	   xiao->command("chat "+"½µÁúÊ®°ËÕÆ£¬ÌìÏÂµÚÒ»ÕÆ·¨£¬¹§Ï²¹§Ï²£¡");
	   if (objectp(ding)) destruct(ding);
	   if (objectp(xiao)) destruct(xiao);	
	   if (objectp(xuanci)) destruct(xuanci);
	   if (objectp(xxdizi)) destruct(xxdizi);
	   //me->add("combat_exp",15000);
	   log_file("quest/xlzsanzhang",sprintf("%s(%s) ÔÚÉÙÁÖ¹ã³¡£¬µÃµ½Ïô·åµÄÇ××ÔÖ¸µã£¬´òÅÜ¶¡´ºÇï¡£¸»Ô´£º%d¡£Ëæ»úÊý£º%d¡£Ê§°Ü£º%d¡£¾­ÑéÖµ£º%d¡£giftÖµ£º%d¡£\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/sanzhao/fail"),me->query("combat_exp"),g,me));
	    me->set("title",HIC"ÄÏÔº´óÍõ"+HIY"Ïô·åÖ¿ÓÑ"NOR);
		me->set("mytitle/quest/xiaofengtitle",HIC"ÄÏÔº´óÍõ"+HIY"Ïô·åÖ¿ÓÑ"NOR);
	   me->set("xlz/sanzhao","pass");
	   me->delete_temp("xlz/askxiao1");
	   me->start_busy(-1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$NËäÈ»ÌýÏô·å½µÁúÊ®°ËÕÆµÄÖÕ¼«°ÂÒå£¬µ«¶ÔÓÚÈçºÎÊ¹ÓÃµÄ¾¢Á¦·¨ÃÅÒ»Ê±Ö®¼äÈ´ÊÇÄÑÒÔÀí½â¡£½µÁúÊ®°ËÕÆµÄ\n"
		+"ÍþÁ¦²¢Ã»ÓÐ·¢»Ó³öÀ´£¬¿´À´Äã»¹ÊÇÓÐ´ýÓÚÖØÐÂ¸úÏô·åÁìÎòÑ§Ï°ÁË¡£Ïô·å¼ûÄãÃ»ÓÐÁìÎò£¬ÇáÌ¾Ò»ÉùµÀ£¬¼ÌÐøÅ¬Á¦£¬ÖÕÓÐÒ»ÌìÄã»áÃ÷°×µÄ¡£\n"NOR,me);
		log_file("quest/xlzsanzhang",sprintf("%8s%-10sÔÚÉÙÁÖ¹ã³¡£¬¿ºÁúÓÐ»ÚÈýÕÐ²¢Ã»ÓÐ³É¹¦£¬ÉÐÐëÅ¬Á¦¡£¸»Ô´£º%d¡£Ëæ»úÊý£º%d¡£Ê§°Ü£º%d¡£¾­ÑéÖµ£º%d¡£giftÖµ£º%d¡£\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/sanzhao/fail"),me->query("combat_exp"),g,me));
		me->add("xlz/sanzhao/fail",1);
		me->set("xlz/sanzhao/time",time());
		me->delete_temp("xlz/askxiao1");
		if (objectp(ding)) destruct(ding);
	    if (objectp(xiao)) destruct(xiao);	
	    if (objectp(xuanci)) destruct(xuanci);
	    if (objectp(xxdizi)) destruct(xxdizi);
		me->start_busy(-1);
        return 1;
	}
    
    
}