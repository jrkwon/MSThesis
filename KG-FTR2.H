/* ****************************** 복합 조사 **************************** */
/* ........................... 보조사 + 보조사 ......................... */
/* .................... 조사 속성이름 중 앞 4자를 조합 ................. */
#define INDETOPI  330               /* 만은                              */
#define INDENSEL  331               /* 만이라도, 뿐이라도(?)             */
#define INDE_TOO  332               /* 만도                              */
#define FROMTOPI  333               /* 부터는                            */
#define FROMINDE  334               /* 부터만                            */
#define FROMNSEL  335               /* 부터라도                          */
#define FROMSPCL  336               /* 부터야말로                        */
#define FROMSELE  337               /* 부터나                            */
#define NOMOTOPI  338               /* 밖에는                            */
#define EACHTOPI  339               /* 씩은                              */
#define EACHINDE  340               /* 씩만                              */
#define EACHNSEL  341               /* 씩이라도, 씩이든지                */
#define EACHNSPC  342               /* 씩인들                            */
#define EACHEMPH  343               /* 씩이나                            */
#define EACHOFCA  344               /* 씩은커녕                          */
#define EACHNOMO  345               /* 씩밖에                            */
#define EACH_TOO  346               /* 씩도                              */
#define TO_TOPIC  347               /* 까지는                            */
#define TO__INDE  348               /* 까지만                            */
#define TO__NSEL  349               /* 까지라도                          */
#define TO__NSPC  350               /* 까지인들                          */
#define TO__OFCA  351               /* 까지는커녕                        */
#define TO__NOMO  352               /* 까지밖에                          */
#define TO__INDI  353               /* 까질랑은                          */
#define TO___TOO  354               /* 까지도                            */
#define FOLL_TOO  355               /* 조차도                            */
/* ...................... 보조사 + 보조사 + 보조사 ..................... */
/* .................... 조사 속성이름 중 앞 3자를 조합 ................. */
#define FROINDTOP 356               /* 부터만은                          */
#define FROINDNSE 357               /* 부터만이라도                      */
#define EACINDTOP 358               /* 씩만은                            */
#define EACINDNSE 359               /* 씩만이라도                        */
#define EACNOMTOP 360               /* 씩밖에는                          */
#define TO_INDTOP 361               /* 까지만은                          */
#define TO_INDNSE 362               /* 까지만이라도                      */
#define TO_NOMTOP 363               /* 까지밖에는                        */
#define INDINDTOP 364               /* 뿐만은                            */
#define INDINDNSE 365               /* 뿐만이라도                        */
/* ........................... 격조사 + 격조사 ......................... */
/* ......................... 처소부사격 + 일반격 ....................... */
/* .................... 조사 속성이름 중 앞 4자를 조합 ................. */
/* 사람에 쓰이는 격과 그렇지 않은 격은 어떻게 구별하나?                  */
#define SPLOSUBJ  370               /* 에서가                            */
#define STLOSUBJ  371               /* 에게가, 한테가                    */
#define SRC_SUBJ  372               /* 에게서가, 한테서가                */
#define GOALSUBJ  373               /* 에게로가, 한테서가                */
#define SPLOPREN  374               /* 에서의                            */
#define SRC_PREN  375               /* 에게서의                          */
#define GOALPREN  376               /* 으로의                            */
#define GOALPREN  376               /* 으로의                            */
/* ........................... 격조사 + 보조사 ......................... */
/* ........................... 부사격 + 보조사 ......................... */
/* .................... 조사 속성이름 중 앞 4자를 조합 ................. */
#define SPLOTOPI  380               /* 장소 ; 에,에서      : 에서는      */
#define TMLOTOPI  381               /* 시간 ; 에           : 에는        */
#define STLOTOPI  382               /* 행위귀착 ; 에,....  : 에게는      */
#define SRC_TOPI  383               /* 출발점 ; 에게,...   : 에서는      */
#define GOALTOPI  384               /* 지향점 ; (으)로,... : (으)로는    */
#define TOOLTOPI  385               /* 도구 ; (으)로(써)   : (으)로써는  */
#define QUALTOPI  386               /* 자격 ; (으)로(서)   : (으)로서는  */
#define CHANTOPI  387               /* 바뀜 ; (으)로       : (으)로는    */
#define CMP_TOPI  388               /* 단순비교 ; 과,와    : 과/와는     */
#define CMPETOPI  389               /* 동등비교 ; 만큼     : 만큼은      */
#define CMPSTOPI  390               /* 그 같음 ; 처럼      : 처럼은      */
#define CMPTTOPI  391               /* 상대비교 ; 보다     : 보다는      */
#define QUADTOPI  392               /* 직접인용 ; -라고    : 라고는      */
#define QUAITOPI  393               /* 간접인용 ; -고      : 고는        */
#define CAUSTOPI  394               /* 원인 ; -에,-(으)로  : 에는        */
#define SPLOINDE  400               /* 장소 ; 에,에서      : 에서만      */
#define TMLOINDE  401               /* 시간 ; 에           : 에만        */
#define STLOINDE  402               /* 행위귀착 ; 에,....  : 에게만      */
#define SRC_INDE  403               /* 출발점 ; 에게,...   : 에서만      */
#define GOALINDE  404               /* 지향점 ; (으)로,... : (으)로만    */
#define TOOLINDE  405               /* 도구 ; (으)로(써)   : (으)로써만  */
#define QUALINDE  406               /* 자격 ; (으)로(서)   : (으)로서만  */
#define CHANINDE  407               /* 바뀜 ; (으)로       : (으)로만    */
#define CMP_INDE  408               /* 단순비교 ; 과,와    : 과/와만     */
#define CMPEINDE  409               /* 동등비교 ; 만큼     : 만큼만      */
#define CMPSINDE  410               /* 그 같음 ; 처럼      : 처럼만      */
#define CMPTINDE  411               /* 상대비교 ; 보다     : 보다만      */
#define QUADINDE  412               /* 직접인용 ; -라고    : 라고만      */
#define QUAIINDE  413               /* 간접인용 ; -고      : 고만        */
#define CAUSINDE  414               /* 원인 ; -에,-(으)로  : 에만        */
#define SPLONSEL  420               /* 장소 ; 에,에서      : 에서라도    */
#define TMLONSEL  421               /* 시간 ; 에           : 에라도      */
#define STLONSEL  422               /* 행위귀착 ; 에,....  : 에게라도    */
#define SRC_NSEL  423               /* 출발점 ; 에게,...   : 에서라도    */
#define GOALNSEL  424               /* 지향점 ; (으)로,... : (으)로라도  */
#define TOOLNSEL  425               /* 도구 ; (으)로(써)   : (으)로써라도*/
#define QUALNSEL  426               /* 자격 ; (으)로(서)   : (으)로서라도*/
#define CHANNSEL  427               /* 바뀜 ; (으)로       : (으)로라도  */
#define CMP_NSEL  428               /* 단순비교 ; 과,와    : 과/와라도   */
#define CMPENSEL  429               /* 동등비교 ; 만큼     : 만큼이라도  */
#define CMPSNSEL  430               /* 그 같음 ; 처럼      : 처럼이라도  */
#define CMPTNSEL  431               /* 상대비교 ; 보다     : 보다라도    */
#define QUADNSEL  432               /* 직접인용 ; -라고    : 라고라도    */
#define QUAINSEL  433               /* 간접인용 ; -고      : 고라도      */
#define CAUSNSEL  434               /* 원인 ; -에,-(으)로  : 에라도      */
#define SPLONSPC  440               /* 장소 ; 에,에서      : 에서인들    */
#define TMLONSPC  441               /* 시간 ; 에           : 엔들        */
#define STLONSPC  442               /* 행위귀착 ; 에,....  : 에게인들    */
#define SRC_NSPC  443               /* 출발점 ; 에게,...   : 에선들      */
#define GOALNSPC  444               /* 지향점 ; (으)로,... : (으)론들    */
#define TOOLNSPC  445               /* 도구 ; (으)로(써)   : (으)로써인들*/
#define QUALNSPC  446               /* 자격 ; (으)로(서)   : (으)로서인들*/
#define CHANNSPC  447               /* 바뀜 ; (으)로       : (으)론들    */
#define CMP_NSPC  448               /* 단순비교 ; 과,와    : 과/와인들   */
#define CMPENSPC  449               /* 동등비교 ; 만큼     : 만큼인들    */
#define CMPSNSPC  450               /* 그 같음 ; 처럼      : 처럼인들    */
#define CMPTNSPC  451               /* 상대비교 ; 보다     : 보단들      */
#define QUADNSPC  452               /* 직접인용 ; -라고    : 라곤들      */
#define QUAINSPC  453               /* 간접인용 ; -고      : 곤들        */
#define CAUSNSPC  454               /* 원인 ; -에,-(으)로  : 엔들        */
#define SPLOFROM  460               /* 장소 ; 에,에서      : 에서부터    */
#define TMLOFROM  461               /* 시간 ; 에           : 에부터      */
#define STLOFROM  462               /* 행위귀착 ; 에,....  : 에게부터    */
#define SRC_FROM  463               /* 출발점 ; 에게,...   : 에서부터    */
#define GOALFROM  464               /* 지향점 ; (으)로,... : (으)로부터  */
#define TOOLFROM  465               /* 도구 ; (으)로(써)   :?(으)로써부터*/
#define QUALFROM  466               /* 자격 ; (으)로(서)   :?(으)로서부터*/
#define CHANFROM  467               /* 바뀜 ; (으)로       :?(으)로부터  */
#define CMP_FROM  468               /* 단순비교 ; 과,와    :?과/와부터   */
#define CMPEFROM  469               /* 동등비교 ; 만큼     :?만큼부터    */
#define CMPSFROM  470               /* 그 같음 ; 처럼      :?처럼부터    */
#define CMPTFROM  471               /* 상대비교 ; 보다     :?보다부터    */
#define QUADFROM  472               /* 직접인용 ; -라고    :?라고부터    */
#define QUAIFROM  473               /* 간접인용 ; -고      :?고부터      */
#define CAUSFROM  474               /* 원인 ; -에,-(으)로  :?에부터      */
#define SPLOSELE  480               /* 장소 ; 에,에서      : 에서나      */
#define TMLOSELE  481               /* 시간 ; 에           : 에나        */
#define STLOSELE  482               /* 행위귀착 ; 에,....  : 에게나      */
#define SRC_SELE  483               /* 출발점 ; 에게,...   : 에서나      */
#define GOALSELE  484               /* 지향점 ; (으)로,... : (으)로나    */
#define TOOLSELE  485               /* 도구 ; (으)로(써)   : (으)로써나  */
#define QUALSELE  486               /* 자격 ; (으)로(서)   : (으)로서나  */
#define CHANSELE  487               /* 바뀜 ; (으)로       : (으)로나    */
#define CMP_SELE  488               /* 단순비교 ; 과,와    :?과/와나     */
#define CMPESELE  489               /* 동등비교 ; 만큼     : 만큼이나    */
#define CMPSSELE  490               /* 그 같음 ; 처럼      : 처럼이나    */
#define CMPTSELE  491               /* 상대비교 ; 보다     : 보다나      */
#define QUADSELE  492               /* 직접인용 ; -라고    : 라고나      */
#define QUAISELE  493               /* 간접인용 ; -고      : 고나        */
#define CAUSSELE  494               /* 원인 ; -에,-(으)로  : 에나        */
#define SPLOSPCL  500               /* 장소 ; 에,에서      : 에서야말로  */
#define TMLOSPCL  501               /* 시간 ; 에           : 에야말로    */
#define STLOSPCL  502               /* 행위귀착 ; 에,....  : 에야말로    */
#define SRC_SPCL  503               /* 출발점 ; 에게,...   : 에서야말로  */
#define GOALSPCL  504               /* 지향점 ; (으)로,... : (으)로야말로*/
#define TOOLSPCL  505               /* 도구 ; (으)로(써)   : (으)로써야..*/
#define QUALSPCL  506               /* 자격 ; (으)로(서)   : (으)로서야..*/
#define CHANSPCL  507               /* 바뀜 ; (으)로       : (으)로야말로*/
#define CMP_SPCL  508               /* 단순비교 ; 과,와    :?과/와야말로 */
#define CMPESPCL  509               /* 동등비교 ; 만큼     : 만큼이야말로*/
#define CMPSSPCL  510               /* 그 같음 ; 처럼      : 처럼이야말로*/
#define CMPTSPCL  511               /* 상대비교 ; 보다     : 보다야말로  */
#define QUADSPCL  512               /* 직접인용 ; -라고    : 라고야말로  */
#define QUAISPCL  513               /* 간접인용 ; -고      : 고야말로    */
#define CAUSSPCL  514               /* 원인 ; -에,-(으)로  : 에야말로    */
#define SPLOOFCA  520               /* 장소 ; 에,에서      : 에서는커녕  */
#define TMLOOFCA  521               /* 시간 ; 에           : 에는커녕    */
#define STLOOFCA  522               /* 행위귀착 ; 에,....  : 에는커녕    */
#define SRC_OFCA  523               /* 출발점 ; 에게,...   : 에서는커녕  */
#define GOALOFCA  524               /* 지향점 ; (으)로,... : (으)로는커녕*/
#define TOOLOFCA  525               /* 도구 ; (으)로(써)   : (으)로써는..*/
#define QUALOFCA  526               /* 자격 ; (으)로(서)   : (으)로서는..*/
#define CHANOFCA  527               /* 바뀜 ; (으)로       : (으)로는커녕*/
#define CMP_OFCA  528               /* 단순비교 ; 과,와    : 과/와는커녕 */
#define CMPEOFCA  529               /* 동등비교 ; 만큼     : 만큼은커녕  */
#define CMPSOFCA  530               /* 그 같음 ; 처럼      : 처럼은커녕  */
#define CMPTOFCA  531               /* 상대비교 ; 보다     : 보다는커녕  */
#define QUADOFCA  532               /* 직접인용 ; -라고    : 라고는커녕  */
#define QUAIOFCA  533               /* 간접인용 ; -고      : 고는커녕    */
#define CAUSOFCA  534               /* 원인 ; -에,-(으)로  : 에는커녕    */
#define SPLONOMO  540               /* 장소 ; 에,에서      : 에서밖에    */
#define TMLONOMO  541               /* 시간 ; 에           : 에밖에      */
#define STLONOMO  542               /* 행위귀착 ; 에,....  : 에밖에      */
#define SRC_NOMO  543               /* 출발점 ; 에게,...   : 에서밖에    */
#define GOALNOMO  544               /* 지향점 ; (으)로,... : (으)로밖에  */
#define TOOLNOMO  545               /* 도구 ; (으)로(써)   : (으)로써는..*/
#define QUALNOMO  546               /* 자격 ; (으)로(서)   : (으)로서는..*/
#define CHANNOMO  547               /* 바뀜 ; (으)로       : (으)로밖에  */
#define CMP_NOMO  548               /* 단순비교 ; 과,와    : 과/와밖에   */
#define CMPENOMO  549               /* 동등비교 ; 만큼     : 만큼밖에    */
#define CMPSNOMO  550               /* 그 같음 ; 처럼      : 처럼밖에    */
#define CMPTNOMO  551               /* 상대비교 ; 보다     : 보다밖에    */
#define QUADNOMO  552               /* 직접인용 ; -라고    : 라고밖에    */
#define QUAINOMO  553               /* 간접인용 ; -고      : 고밖에      */
#define CAUSNOMO  554               /* 원인 ; -에,-(으)로  : 에밖에      */
#define SPLOINDI  560               /* 장소 ; 에,에서      : 에설랑은    */
#define TMLOINDI  561               /* 시간 ; 에           : 엘랑은      */
#define STLOINDI  562               /* 행위귀착 ; 에,....  : 엘랑은      */
#define SRC_INDI  563               /* 출발점 ; 에게,...   : 에설랑은    */
#define GOALINDI  564               /* 지향점 ; (으)로,... : (으)롤랑은  */
#define TOOLINDI  565               /* 도구 ; (으)로(써)   : (으)로썰랑은*/
#define QUALINDI  566               /* 자격 ; (으)로(서)   : (으)로설랑은*/
#define CHANINDI  567               /* 바뀜 ; (으)로       : (으)롤랑은  */
#define CMP_INDI  568               /* 단순비교 ; 과,와    : 과/와ㄹ랑은 */
#define CMPEINDI  569               /* 동등비교 ; 만큼     : 만큼일랑은  */
#define CMPSINDI  570               /* 그 같음 ; 처럼      : 처럼일랑은  */
#define CMPTINDI  571               /* 상대비교 ; 보다     : 보달랑은    */
#define QUADINDI  572               /* 직접인용 ; -라고    : 라골랑은    */
#define QUAIINDI  573               /* 간접인용 ; -고      : 골랑은      */
#define CAUSINDI  574               /* 원인 ; -에,-(으)로  : 엘랑은      */
#define SPLOEXPA  580               /* 장소 ; 에,에서      : 에서나      */
#define TMLOEXPA  581               /* 시간 ; 에           : 에나        */
#define STLOEXPA  582               /* 행위귀착 ; 에,....  : 에나        */
#define SRC_EXPA  583               /* 출발점 ; 에게,...   : 에서나      */
#define GOALEXPA  584               /* 지향점 ; (으)로,... : (으)로나    */
#define TOOLEXPA  585               /* 도구 ; (으)로(써)   : (으)로써나  */
#define QUALEXPA  586               /* 자격 ; (으)로(서)   : (으)로서나  */
#define CHANEXPA  587               /* 바뀜 ; (으)로       : (으)로나    */
#define CMP_EXPA  588               /* 단순비교 ; 과,와    : 과/와나     */
#define CMPEEXPA  589               /* 동등비교 ; 만큼     : 만큼이나    */
#define CMPSEXPA  590               /* 그 같음 ; 처럼      : 처럼이나    */
#define CMPTEXPA  591               /* 상대비교 ; 보다     : 보다나      */
#define QUADEXPA  592               /* 직접인용 ; -라고    : 라고나      */
#define QUAIEXPA  593               /* 간접인용 ; -고      : 고나        */
#define CAUSEXPA  594               /* 원인 ; -에,-(으)로  : 에나        */
#define SPLODISS  600               /* 장소 ; 에,에서      : 에서나마    */
#define TMLODISS  601               /* 시간 ; 에           : 에나마      */
#define STLODISS  602               /* 행위귀착 ; 에,....  : 에나마      */
#define SRC_DISS  603               /* 출발점 ; 에게,...   : 에서나마    */
#define GOALDISS  604               /* 지향점 ; (으)로,... : (으)로나마  */
#define TOOLDISS  605               /* 도구 ; (으)로(써)   : (으)로써나마*/
#define QUALDISS  606               /* 자격 ; (으)로(서)   : (으)로서나마*/
#define CHANDISS  607               /* 바뀜 ; (으)로       : (으)로나마  */
#define CMP_DISS  608               /* 단순비교 ; 과,와    : 과/와나마   */
#define CMPEDISS  609               /* 동등비교 ; 만큼     : 만큼이나마  */
#define CMPSDISS  610               /* 그 같음 ; 처럼      : 처럼이나마  */
#define CMPTDISS  611               /* 상대비교 ; 보다     : 보다나마    */
#define QUADDISS  612               /* 직접인용 ; -라고    : 라고나마    */
#define QUAIDISS  613               /* 간접인용 ; -고      : 고나마      */
#define CAUSDISS  614               /* 원인 ; -에,-(으)로  : 에나마      */
#define SPLOEMPH  610               /* 장소 ; 에,에서      : 에서나      */
#define TMLOEMPH  611               /* 시간 ; 에           : 에나        */
#define STLOEMPH  612               /* 행위귀착 ; 에,....  : 에나        */
#define SRC_EMPH  613               /* 출발점 ; 에게,...   : 에서나      */
#define GOALEMPH  614               /* 지향점 ; (으)로,... : (으)로나    */
#define TOOLEMPH  615               /* 도구 ; (으)로(써)   : (으)로써나  */
#define QUALEMPH  616               /* 자격 ; (으)로(서)   : (으)로서나  */
#define CHANEMPH  617               /* 바뀜 ; (으)로       : (으)로나    */
#define CMP_EMPH  618               /* 단순비교 ; 과,와    : 과/와나     */
#define CMPEEMPH  619               /* 동등비교 ; 만큼     : 만큼이나    */
#define CMPSEMPH  620               /* 그 같음 ; 처럼      : 처럼이나    */
#define CMPTEMPH  621               /* 상대비교 ; 보다     : 보다나      */
#define QUADEMPH  622               /* 직접인용 ; -라고    : 라고나      */
#define QUAIEMPH  623               /* 간접인용 ; -고      : 고나        */
#define CAUSEMPH  624               /* 원인 ; -에,-(으)로  : 에나        */
#define SPLOUNIF  630               /* 장소 ; 에,에서      : 에서마다    */
#define TMLOUNIF  631               /* 시간 ; 에           : 에마다      */
#define STLOUNIF  632               /* 행위귀착 ; 에,....  : 에마다      */
#define SRC_UNIF  633               /* 출발점 ; 에게,...   : 에서마다    */
#define GOALUNIF  634               /* 지향점 ; (으)로,... : (으)로마다  */
#define TOOLUNIF  635               /* 도구 ; (으)로(써)   : (으)로써마다*/
#define QUALUNIF  636               /* 자격 ; (으)로(서)   : (으)로서마다*/
#define CHANUNIF  637               /* 바뀜 ; (으)로       : (으)로나마다*/
#define CMP_UNIF  638               /* 단순비교 ; 과,와    : 과/와마다   */
#define CMPEUNIF  639               /* 동등비교 ; 만큼     : 만큼마다    */
#define CMPSUNIF  640               /* 그 같음 ; 처럼      : 처럼마다    */
#define CMPTUNIF  641               /* 상대비교 ; 보다     : 보다마다    */
#define QUADUNIF  642               /* 직접인용 ; -라고    : 라고마다    */
#define QUAIUNIF  643               /* 간접인용 ; -고      : 고마다      */
#define CAUSUNIF  644               /* 원인 ; -에,-(으)로  : 에마다      */
#define SPLO__TO  650               /* 장소 ; 에,에서      : 에서까지    */
#define TMLO__TO  651               /* 시간 ; 에           : 에까지      */
#define STLO__TO  652               /* 행위귀착 ; 에,....  : 에까지      */
#define SRC___TO  653               /* 출발점 ; 에게,...   : 에서까지    */
#define GOAL__TO  654               /* 지향점 ; (으)로,... : (으)로까지  */
#define TOOL__TO  655               /* 도구 ; (으)로(써)   : (으)로써까지*/
#define QUAL__TO  656               /* 자격 ; (으)로(서)   : (으)로서까지*/
#define CHAN__TO  657               /* 바뀜 ; (으)로       : (으)로까지  */
#define CMP___TO  658               /* 단순비교 ; 과,와    : 과/와까지   */
#define CMPE__TO  659               /* 동등비교 ; 만큼     : 만큼까지    */
#define CMPS__TO  660               /* 그 같음 ; 처럼      : 처럼까지    */
#define CMPT__TO  661               /* 상대비교 ; 보다     : 보다까지    */
#define QUAD__TO  662               /* 직접인용 ; -라고    : 라고까지    */
#define QUAI__TO  663               /* 간접인용 ; -고      : 고까지      */
#define CAUS__TO  664               /* 원인 ; -에,-(으)로  : 에까지      */
#define SPLO_TOO  660               /* 장소 ; 에,에서      : 에서도      */
#define TMLO_TOO  661               /* 시간 ; 에           : 에도        */
#define STLO_TOO  662               /* 행위귀착 ; 에,....  : 에도        */
#define SRC__TOO  663               /* 출발점 ; 에게,...   : 에서도      */
#define GOAL_TOO  664               /* 지향점 ; (으)로,... : (으)로도    */
#define TOOL_TOO  665               /* 도구 ; (으)로(써)   : (으)로써도  */
#define QUAL_TOO  666               /* 자격 ; (으)로(서)   : (으)로서도  */
#define CHAN_TOO  667               /* 바뀜 ; (으)로       : (으)로도    */
#define CMP__TOO  668               /* 단순비교 ; 과,와    : 과/와도     */
#define CMPE_TOO  669               /* 동등비교 ; 만큼     : 만큼도      */
#define CMPS_TOO  670               /* 그 같음 ; 처럼      : 처럼도      */
#define CMPT_TOO  671               /* 상대비교 ; 보다     : 보다도      */
#define QUAD_TOO  672               /* 직접인용 ; -라고    : 라고도      */
#define QUAI_TOO  673               /* 간접인용 ; -고      : 고도        */
#define CAUS_TOO  674               /* 원인 ; -에,-(으)로  : 에도        */
#define SPLOFOLL  680               /* 장소 ; 에,에서      : 에서조차    */
#define TMLOFOLL  681               /* 시간 ; 에           : 에조차      */
#define STLOFOLL  682               /* 행위귀착 ; 에,....  : 에조차      */
#define SRC_FOLL  683               /* 출발점 ; 에게,...   : 에서조차    */
#define GOALFOLL  684               /* 지향점 ; (으)로,... : (으)로조차  */
#define TOOLFOLL  685               /* 도구 ; (으)로(써)   : (으)로써조차*/
#define QUALFOLL  686               /* 자격 ; (으)로(서)   : (으)로서조차*/
#define CHANFOLL  687               /* 바뀜 ; (으)로       : (으)로조차  */
#define CMP_FOLL  688               /* 단순비교 ; 과,와    : 과/와조차   */
#define CMPEFOLL  689               /* 동등비교 ; 만큼     : 만큼조차    */
#define CMPSFOLL  690               /* 그 같음 ; 처럼      : 처럼조차    */
#define CMPTFOLL  691               /* 상대비교 ; 보다     : 보다조차    */
#define QUADFOLL  692               /* 직접인용 ; -라고    : 라고조차    */
#define QUAIFOLL  693               /* 간접인용 ; -고      : 고조차      */
#define CAUSFOLL  694               /* 원인 ; -에,-(으)로  : 에조차      */
/* .................... 격조사 + 보조사 + 보조사 ....................... */
/* .................... 부사격 + 보조사 + 보조사 ....................... */
/* .................... 조사 속성이름 중 앞 3자를 조합 ................. */
#define SPLINDTOP 700               /* 장소 ; 에,에서      : 에서만은    */
#define TMLINDTOP 701               /* 시간 ; 에           : 에만은      */
#define STLINDTOP 702               /* 행위귀착 ; 에,....  : 에게만은    */
#define SRCINDTOP 703               /* 출발점 ; 에게,...   : 에서만은    */
#define GOAINDTOP 704               /* 지향점 ; (으)로,... : (으)로만은  */
#define TOOINDTOP 705               /* 도구 ; (으)로(써)   : (으)로써만은*/
#define QULINDTOP 706               /* 자격 ; (으)로(서)   : (으)로서만은*/
#define CHAINDTOP 707               /* 바뀜 ; (으)로       : (으)로만은  */
#define CM_INDTOP 708               /* 단순비교 ; 과,와    : 과/와만은   */
#define CMEINDTOP 709               /* 동등비교 ; 만큼     : 만큼만은    */
#define CMSINDTOP 710               /* 그 같음 ; 처럼      : 처럼만은    */
#define CMPINDTOP 711               /* 상대비교 ; 보다     : 보다만은    */
#define QUDINDTOP 712               /* 직접인용 ; -라고    : 라고만은    */
#define QUIINDTOP 713               /* 간접인용 ; -고      : 고만은      */
#define CAUINDTOP 714               /* 원인 ; -에,-(으)로  : 에만은      */
#define SPLINDNSE 720               /* 장소 ; 에,에서      : 에서만이라도*/
#define TMLINDNSE 721               /* 시간 ; 에           : 에만이라도  */
#define STLINDNSE 722               /* 행위귀착 ; 에,....  : 에게만이라도*/
#define SRCINDNSE 723               /* 출발점 ; 에게,...   : 에서만이라도*/
#define GOAINDNSE 724               /* 지향점 ; (으)로,... : (으)로만이..*/
#define TOOINDNSE 725               /* 도구 ; (으)로(써)   : (으)로써만..*/
#define QULINDNSE 726               /* 자격 ; (으)로(서)   : (으)로서만..*/
#define CHAINDNSE 727               /* 바뀜 ; (으)로       : (으)로만이..*/
#define CM_INDNSE 728               /* 단순비교 ; 과,와    : 과/와만이라.*/
#define CMEINDNSE 729               /* 동등비교 ; 만큼     : 만큼만이라도*/
#define CMSINDNSE 730               /* 그 같음 ; 처럼      : 처럼만이라도*/
#define CMPINDNSE 731               /* 상대비교 ; 보다     : 보다만이라도*/
#define QUDINDNSE 732               /* 직접인용 ; -라고    : 라고만이라도*/
#define QUIINDNSE 733               /* 간접인용 ; -고      : 고만이라도  */
#define CAUINDNSE 734               /* 원인 ; -에,-(으)로  : 에만이라도  */
#define SPLINDTOO 740               /* 장소 ; 에,에서      : 에서만도    */
#define TMLINDTOO 741               /* 시간 ; 에           : 에만도      */
#define STLINDTOO 742               /* 행위귀착 ; 에,....  : 에게만도    */
#define SRCINDTOO 743               /* 출발점 ; 에게,...   : 에서만도    */
#define GOAINDTOO 744               /* 지향점 ; (으)로,... : (으)로만도  */
#define TOOINDTOO 745               /* 도구 ; (으)로(써)   : (으)로써만도*/
#define QULINDTOO 746               /* 자격 ; (으)로(서)   : (으)로서만도*/
#define CHAINDTOO 747               /* 바뀜 ; (으)로       : (으)로만도  */
#define CM_INDTOO 748               /* 단순비교 ; 과,와    : 과/와만도   */
#define CMEINDTOO 749               /* 동등비교 ; 만큼     : 만큼만도    */
#define CMSINDTOO 750               /* 그 같음 ; 처럼      : 처럼만도    */
#define CMPINDTOO 751               /* 상대비교 ; 보다     : 보다만도    */
#define QUDINDTOO 752               /* 직접인용 ; -라고    : 라고만도    */
#define QUIINDTOO 753               /* 간접인용 ; -고      : 고만도      */
#define CAUINDTOO 754               /* 원인 ; -에,-(으)로  : 에만도      */
#define SPLFROTOP 740               /* 장소 ; 에,에서      : 에서부터는  */
#define TMLFROTOP 741               /* 시간 ; 에           : 에부터는    */
#define STLFROTOP 742               /* 행위귀착 ; 에,....  : 에게부터는  */
#define SRCFROTOP 743               /* 출발점 ; 에게,...   : 에서부터는  */
#define GOAFROTOP 744               /* 지향점 ; (으)로,... : (으)로부터는*/
#define FROFROTOP 745               /* 도구 ; (으)로(써)   : (으)로써부..*/
#define QULFROTOP 746               /* 자격 ; (으)로(서)   : (으)로서부..*/
#define CHAFROTOP 747               /* 바뀜 ; (으)로       : (으)로부터는*/
#define CM_FROTOP 748               /* 단순비교 ; 과,와    : 과/와부터는 */
#define CMEFROTOP 749               /* 동등비교 ; 만큼     : 만큼부터는  */
#define CMSFROTOP 750               /* 그 같음 ; 처럼      : 처럼부터는  */
#define CMPFROTOP 751               /* 상대비교 ; 보다     : 보다부터는  */
#define QUDFROTOP 752               /* 직접인용 ; -라고    : 라고부터는  */
#define QUIFROTOP 753               /* 간접인용 ; -고      : 고부터는    */
#define CAUFROTOP 754               /* 원인 ; -에,-(으)로  : 에부터는    */
#define SPLFROIND 760               /* 장소 ; 에,에서      : 에서부터만  */
#define TMLFROIND 761               /* 시간 ; 에           : 에부터만    */
#define STLFROIND 762               /* 행위귀착 ; 에,....  : 에게부터만  */
#define SRCFROIND 763               /* 출발점 ; 에게,...   : 에서부터만  */
#define GOAFROIND 764               /* 지향점 ; (으)로,... : (으)로부터만*/
#define FROFROIND 765               /* 도구 ; (으)로(써)   : (으)로써부..*/
#define QULFROIND 766               /* 자격 ; (으)로(서)   : (으)로서부..*/
#define CHAFROIND 767               /* 바뀜 ; (으)로       : (으)로부터만*/
#define CM_FROIND 768               /* 단순비교 ; 과,와    : 과/와부터만 */
#define CMEFROIND 769               /* 동등비교 ; 만큼     : 만큼부터만  */
#define CMSFROIND 770               /* 그 같음 ; 처럼      : 처럼부터만  */
#define CMPFROIND 771               /* 상대비교 ; 보다     : 보다부터만  */
#define QUDFROIND 772               /* 직접인용 ; -라고    : 라고부터만  */
#define QUIFROIND 773               /* 간접인용 ; -고      : 고부터만    */
#define CAUFROIND 774               /* 원인 ; -에,-(으)로  : 에부터만    */
#define SPLFRONSE 780               /* 장소 ; 에,에서      : 에서부터라도*/
#define TMLFRONSE 781               /* 시간 ; 에           : 에부터라도  */
#define STLFRONSE 782               /* 행위귀착 ; 에,....  : 에게부터라도*/
#define SRCFRONSE 783               /* 출발점 ; 에게,...   : 에서부터라도*/
#define GOAFRONSE 784               /* 지향점 ; (으)로,... : (으)로부터..*/
#define FROFRONSE 785               /* 도구 ; (으)로(써)   : (으)로써부..*/
#define QULFRONSE 786               /* 자격 ; (으)로(서)   : (으)로서부..*/
#define CHAFRONSE 787               /* 바뀜 ; (으)로       : (으)로부터..*/
#define CM_FRONSE 788               /* 단순비교 ; 과,와    : 과/와부터.. */
#define CMEFRONSE 789               /* 동등비교 ; 만큼     : 만큼부터라도*/
#define CMSFRONSE 790               /* 그 같음 ; 처럼      : 처럼부터라도*/
#define CMPFRONSE 791               /* 상대비교 ; 보다     : 보다부터라도*/
#define QUDFRONSE 792               /* 직접인용 ; -라고    : 라고부터라도*/
#define QUIFRONSE 793               /* 간접인용 ; -고      : 고부터라도  */
#define CAUFRONSE 794               /* 원인 ; -에,-(으)로  : 에부터라도  */
#define SPLFROSPC 800               /* 장소 ; 에,에서      : 에서부터야..*/
#define TMLFROSPC 801               /* 시간 ; 에           : 에부터야말로*/
#define STLFROSPC 802               /* 행위귀착 ; 에,....  : 에게부터야..*/
#define SRCFROSPC 803               /* 출발점 ; 에게,...   : 에서부터야..*/
#define GOAFROSPC 804               /* 지향점 ; (으)로,... : (으)로부터..*/
#define FROFROSPC 805               /* 도구 ; (으)로(써)   : (으)로써부..*/
#define QULFROSPC 806               /* 자격 ; (으)로(서)   : (으)로서부..*/
#define CHAFROSPC 807               /* 바뀜 ; (으)로       : (으)로부터..*/
#define CM_FROSPC 808               /* 단순비교 ; 과,와    : 과/와부터.. */
#define CMEFROSPC 809               /* 동등비교 ; 만큼     : 만큼부터야..*/
#define CMSFROSPC 810               /* 그 같음 ; 처럼      : 처럼부터야..*/
#define CMPFROSPC 811               /* 상대비교 ; 보다     : 보다부터야..*/
#define QUDFROSPC 812               /* 직접인용 ; -라고    : 라고부터야..*/
#define QUIFROSPC 813               /* 간접인용 ; -고      : 고부터야말로*/
#define CAUFROSPC 814               /* 원인 ; -에,-(으)로  : 에부터야말로*/
#define SPLFROEMP 820               /* 장소 ; 에,에서      : 에서부터나  */
#define TMLFROEMP 821               /* 시간 ; 에           : 에부터나    */
#define STLFROEMP 822               /* 행위귀착 ; 에,....  : 에게부터나  */
#define SRCFROEMP 823               /* 출발점 ; 에게,...   : 에서부터나  */
#define GOAFROEMP 824               /* 지향점 ; (으)로,... : (으)로부터나*/
#define FROFROEMP 825               /* 도구 ; (으)로(써)   : (으)로써부..*/
#define QULFROEMP 826               /* 자격 ; (으)로(서)   : (으)로서부..*/
#define CHAFROEMP 827               /* 바뀜 ; (으)로       : (으)로부터나*/
#define CM_FROEMP 828               /* 단순비교 ; 과,와    : 과/와부터나 */
#define CMEFROEMP 829               /* 동등비교 ; 만큼     : 만큼부터나  */
#define CMSFROEMP 830               /* 그 같음 ; 처럼      : 처럼부터나  */
#define CMPFROEMP 831               /* 상대비교 ; 보다     : 보다부터나  */
#define QUDFROEMP 832               /* 직접인용 ; -라고    : 라고부터나  */
#define QUIFROEMP 833               /* 간접인용 ; -고      : 고부터나    */
#define CAUFROEMP 834               /* 원인 ; -에,-(으)로  : 에부터나    */
#define SPLNOMTOP 840               /* 장소 ; 에,에서      : 에서밖에는  */
#define TMLNOMTOP 841               /* 시간 ; 에           : 에밖에는    */
#define STLNOMTOP 842               /* 행위귀착 ; 에,....  : 에게밖에는  */
#define SRCNOMTOP 843               /* 출발점 ; 에게,...   : 에서밖에는  */
#define GOANOMTOP 844               /* 지향점 ; (으)로,... : (으)로밖에는*/
#define NOMNOMTOP 845               /* 도구 ; (으)로(써)   : (으)로써밖..*/
#define QULNOMTOP 846               /* 자격 ; (으)로(서)   : (으)로서밖..*/
#define CHANOMTOP 847               /* 바뀜 ; (으)로       : (으)로밖에는*/
#define CM_NOMTOP 848               /* 단순비교 ; 과,와    : 과/와밖에는 */
#define CMENOMTOP 849               /* 동등비교 ; 만큼     : 만큼밖에는  */
#define CMSNOMTOP 840               /* 그 같음 ; 처럼      : 처럼밖에는  */
#define CMPNOMTOP 841               /* 상대비교 ; 보다     : 보다밖에는  */
#define QUDNOMTOP 842               /* 직접인용 ; -라고    : 라고밖에는  */
#define QUINOMTOP 843               /* 간접인용 ; -고      : 고밖에는    */
#define CAUNOMTOP 844               /* 원인 ; -에,-(으)로  : 에밖에는    */
#define SPL_TOTOP 850               /* 장소 ; 에,에서      : 에서까지는  */
#define TML_TOTOP 851               /* 시간 ; 에           : 에까지는    */
#define STL_TOTOP 852               /* 행위귀착 ; 에,....  : 에게까지는  */
#define SRC_TOTOP 853               /* 출발점 ; 에게,...   : 에서까지는  */
#define GOA_TOTOP 854               /* 지향점 ; (으)로,... : (으)로까지는*/
#define _TO_TOTOP 855               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TOTOP 856               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TOTOP 857               /* 바뀜 ; (으)로       : (으)로까지는*/
#define CM__TOTOP 858               /* 단순비교 ; 과,와    : 과/와까지는 */
#define CME_TOTOP 859               /* 동등비교 ; 만큼     : 만큼까지는  */
#define CMS_TOTOP 860               /* 그 같음 ; 처럼      : 처럼까지는  */
#define CMP_TOTOP 861               /* 상대비교 ; 보다     : 보다까지는  */
#define QUD_TOTOP 862               /* 직접인용 ; -라고    : 라고까지는  */
#define QUI_TOTOP 863               /* 간접인용 ; -고      : 고까지는    */
#define CAU_TOTOP 864               /* 원인 ; -에,-(으)로  : 에까지는    */
#define SPL_TOIND 870               /* 장소 ; 에,에서      : 에서까지만  */
#define TML_TOIND 871               /* 시간 ; 에           : 에까지만    */
#define STL_TOIND 872               /* 행위귀착 ; 에,....  : 에게까지만  */
#define SRC_TOIND 873               /* 출발점 ; 에게,...   : 에서까지만  */
#define GOA_TOIND 874               /* 지향점 ; (으)로,... : (으)로까지만*/
#define _TO_TOIND 875               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TOIND 876               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TOIND 877               /* 바뀜 ; (으)로       : (으)로까지만*/
#define CM__TOIND 878               /* 단순비교 ; 과,와    : 과/와까지만 */
#define CME_TOIND 879               /* 동등비교 ; 만큼     : 만큼까지만  */
#define CMS_TOIND 880               /* 그 같음 ; 처럼      : 처럼까지만  */
#define CMP_TOIND 881               /* 상대비교 ; 보다     : 보다까지만  */
#define QUD_TOIND 882               /* 직접인용 ; -라고    : 라고까지만  */
#define QUI_TOIND 883               /* 간접인용 ; -고      : 고까지만    */
#define CAU_TOIND 884               /* 원인 ; -에,-(으)로  : 에까지만    */
#define SPL_TONSE 890               /* 장소 ; 에,에서      : 에서까지라도*/
#define TML_TONSE 891               /* 시간 ; 에           : 에까지라도  */
#define STL_TONSE 892               /* 행위귀착 ; 에,....  : 에게까지라도*/
#define SRC_TONSE 893               /* 출발점 ; 에게,...   : 에서까지라도*/
#define GOA_TONSE 894               /* 지향점 ; (으)로,... : (으)로까지..*/
#define _TO_TONSE 895               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TONSE 896               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TONSE 897               /* 바뀜 ; (으)로       : (으)로까지..*/
#define CM__TONSE 898               /* 단순비교 ; 과,와    : 과/와까지.. */
#define CME_TONSE 899               /* 동등비교 ; 만큼     : 만큼까지라도*/
#define CMS_TONSE 890               /* 그 같음 ; 처럼      : 처럼까지라도*/
#define CMP_TONSE 901               /* 상대비교 ; 보다     : 보다까지라도*/
#define QUD_TONSE 902               /* 직접인용 ; -라고    : 라고까지라도*/
#define QUI_TONSE 903               /* 간접인용 ; -고      : 고까지라도  */
#define CAU_TONSE 904               /* 원인 ; -에,-(으)로  : 에까지라도  */
#define SPL_TONSP 910               /* 장소 ; 에,에서      : 에서까진들  */
#define TML_TONSP 911               /* 시간 ; 에           : 에까진들    */
#define STL_TONSP 912               /* 행위귀착 ; 에,....  : 에게까진들  */
#define SRC_TONSP 913               /* 출발점 ; 에게,...   : 에서까진들  */
#define GOA_TONSP 914               /* 지향점 ; (으)로,... : (으)로까진..*/
#define _TO_TONSP 915               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TONSP 916               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TONSP 917               /* 바뀜 ; (으)로       : (으)로까진..*/
#define CM__TONSP 918               /* 단순비교 ; 과,와    : 과/와까진들 */
#define CME_TONSP 919               /* 동등비교 ; 만큼     : 만큼까진들  */
#define CMS_TONSP 920               /* 그 같음 ; 처럼      : 처럼까진들  */
#define CMP_TONSP 921               /* 상대비교 ; 보다     : 보다까진들  */
#define QUD_TONSP 922               /* 직접인용 ; -라고    : 라고까진들  */
#define QUI_TONSP 923               /* 간접인용 ; -고      : 고까진들    */
#define CAU_TONSP 924               /* 원인 ; -에,-(으)로  : 에까진들    */
#define SPL_TOOFC 930               /* 장소 ; 에,에서      : 에서까지는..*/
#define TML_TOOFC 931               /* 시간 ; 에           : 에까지는커녕*/
#define STL_TOOFC 932               /* 행위귀착 ; 에,....  : 에게까지는..*/
#define SRC_TOOFC 933               /* 출발점 ; 에게,...   : 에서까지는..*/
#define GOA_TOOFC 934               /* 지향점 ; (으)로,... : (으)로까지..*/
#define _TO_TOOFC 935               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TOOFC 936               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TOOFC 937               /* 바뀜 ; (으)로       : (으)로까지..*/
#define CM__TOOFC 938               /* 단순비교 ; 과,와    : 과/와까지.. */
#define CME_TOOFC 939               /* 동등비교 ; 만큼     : 만큼까지는..*/
#define CMS_TOOFC 930               /* 그 같음 ; 처럼      : 처럼까지는..*/
#define CMP_TOOFC 931               /* 상대비교 ; 보다     : 보다까지는..*/
#define QUD_TOOFC 932               /* 직접인용 ; -라고    : 라고까지는..*/
#define QUI_TOOFC 933               /* 간접인용 ; -고      : 고까지는커녕*/
#define CAU_TOOFC 934               /* 원인 ; -에,-(으)로  : 에까지는커녕*/
#define SPL_TONOM 940               /* 장소 ; 에,에서      : 에서까지밖..*/
#define TML_TONOM 941               /* 시간 ; 에           : 에까지밖에  */
#define STL_TONOM 942               /* 행위귀착 ; 에,....  : 에게까지밖..*/
#define SRC_TONOM 943               /* 출발점 ; 에게,...   : 에서까지밖..*/
#define GOA_TONOM 944               /* 지향점 ; (으)로,... : (으)로까지..*/
#define _TO_TONOM 945               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TONOM 946               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TONOM 947               /* 바뀜 ; (으)로       : (으)로까지..*/
#define CM__TONOM 948               /* 단순비교 ; 과,와    : 과/와까지.. */
#define CME_TONOM 949               /* 동등비교 ; 만큼     : 만큼까지밖에*/
#define CMS_TONOM 950               /* 그 같음 ; 처럼      : 처럼까지밖에*/
#define CMP_TONOM 951               /* 상대비교 ; 보다     : 보다까지밖에*/
#define QUD_TONOM 952               /* 직접인용 ; -라고    : 라고까지밖에*/
#define QUI_TONOM 953               /* 간접인용 ; -고      : 고까지밖에  */
#define CAU_TONOM 954               /* 원인 ; -에,-(으)로  : 에까지밖에  */
#define SPL_TOTOO 960               /* 장소 ; 에,에서      : 에서까지도  */
#define TML_TOTOO 961               /* 시간 ; 에           : 에까지도    */
#define STL_TOTOO 962               /* 행위귀착 ; 에,....  : 에게까지도  */
#define SRC_TOTOO 963               /* 출발점 ; 에게,...   : 에서까지도  */
#define GOA_TOTOO 964               /* 지향점 ; (으)로,... : (으)로까지도*/
#define _TO_TOTOO 965               /* 도구 ; (으)로(써)   : (으)로써까..*/
#define QUL_TOTOO 966               /* 자격 ; (으)로(서)   : (으)로서까..*/
#define CHA_TOTOO 967               /* 바뀜 ; (으)로       : (으)로까지도*/
#define CM__TOTOO 968               /* 단순비교 ; 과,와    : 과/와까지도 */
#define CME_TOTOO 969               /* 동등비교 ; 만큼     : 만큼까지도  */
#define CMS_TOTOO 970               /* 그 같음 ; 처럼      : 처럼까지도  */
#define CMP_TOTOO 971               /* 상대비교 ; 보다     : 보다까지도  */
#define QUD_TOTOO 972               /* 직접인용 ; -라고    : 라고까지도  */
#define QUI_TOTOO 973               /* 간접인용 ; -고      : 고까지도    */
#define CAU_TOTOO 974               /* 원인 ; -에,-(으)로  : 에까지도    */
#define SPLFOLTOO 980               /* 장소 ; 에,에서      : 에서조차도  */
#define TMLFOLTOO 981               /* 시간 ; 에           : 에조차도    */
#define STLFOLTOO 982               /* 행위귀착 ; 에,....  : 에게조차도  */
#define SRCFOLTOO 983               /* 출발점 ; 에게,...   : 에서조차도  */
#define GOAFOLTOO 984               /* 지향점 ; (으)로,... : (으)로조차도*/
#define FOLFOLTOO 985               /* 도구 ; (으)로(써)   : (으)로써조..*/
#define QULFOLTOO 986               /* 자격 ; (으)로(서)   : (으)로서조..*/
#define CHAFOLTOO 987               /* 바뀜 ; (으)로       : (으)로조차도*/
#define CM_FOLTOO 988               /* 단순비교 ; 과,와    : 과/와조차도 */
#define CMEFOLTOO 989               /* 동등비교 ; 만큼     : 만큼조차도  */
#define CMSFOLTOO 990               /* 그 같음 ; 처럼      : 처럼조차도  */
#define CMPFOLTOO 991               /* 상대비교 ; 보다     : 보다조차도  */
#define QUDFOLTOO 992               /* 직접인용 ; -라고    : 라고조차도  */
#define QUIFOLTOO 993               /* 간접인용 ; -고      : 고조차도    */
#define CAUFOLTOO 994               /* 원인 ; -에,-(으)로  : 에조차도    */
/* ................. 격조사 + 보조사 + 보조사 + 보조사 ................. */
/* ..................부사격 + 보조사 + 보조사 + 보조사 ................. */
/* .................... 조사 속성이름 중 앞 3자를 조합 ................. */
#define SPLFROINDTOP     1000       /* 장소 ; 에,에서      : 에서부터만은*/
#define TMLFROINDTOP     1001       /* 시간 ; 에           : 에부터만은  */
#define STLFROINDTOP     1002       /* 행위귀착 ; 에,....  : 에게부터만은*/
#define SRCFROINDTOP     1003       /* 출발점 ; 에게,...   : 에서부터만은*/
#define GOAFROINDTOP     1004       /* 지향점 ; (으)로,... : (으)로부터..*/
#define FOLFROINDTOP     1005       /* 도구 ; (으)로(써)   : (으)로써부..*/
#define QULFROINDTOP     1006       /* 자격 ; (으)로(서)   : (으)로서부..*/
#define CHAFROINDTOP     1007       /* 바뀜 ; (으)로       : (으)로부터..*/
#define CM_FROINDTOP     1008       /* 단순비교 ; 과,와    : 과/와부터.. */
#define CMEFROINDTOP     1009       /* 동등비교 ; 만큼     : 만큼부터만은*/
#define CMSFROINDTOP     1010       /* 그 같음 ; 처럼      : 처럼부터만은*/
#define CMPFROINDTOP     1011       /* 상대비교 ; 보다     : 보다부터만은*/
#define QUDFROINDTOP     1012       /* 직접인용 ; -라고    : 라고부터만은*/
#define QUIFROINDTOP     1013       /* 간접인용 ; -고      : 고부터만은  */
#define CAUFROINDTOP     1014       /* 원인 ; -에,-(으)로  : 에부터만은  */
#define SPLFROINDNSE     1020       /* 장소 ; 에,에서   :에서부터만이라도*/
#define TMLFROINDNSE     1021       /* 시간 ; 에        :에부터만이라도  */
#define STLFROINDNSE     1022       /* 행위귀착 ; 에,...:에게부터만이라도*/
#define SRCFROINDNSE     1023       /* 출발점 ; 에게,...:에서부터만이라도*/
#define GOAFROINDNSE     1024       /* 지향점 ; (으)로,.:으로부터만이라도*/
#define FOLFROINDNSE     1025       /* 도구 ; (으)로(써):으로써부터만이..*/
#define QULFROINDNSE     1026       /* 자격 ; (으)로(서):으로서부터만이..*/
#define CHAFROINDNSE     1027       /* 바뀜 ; (으)로    :으로부터만이라도*/
#define CM_FROINDNSE     1028       /* 단순비교 ; 과,와 :과부터만이라도  */
#define CMEFROINDNSE     1029       /* 동등비교 ; 만큼  :만큼부터만이라도*/
#define CMSFROINDNSE     1030       /* 그 같음 ; 처럼   :처럼부터만이라도*/
#define CMPFROINDNSE     1031       /* 상대비교 ; 보다  :보다부터만이라도*/
#define QUDFROINDNSE     1032       /* 직접인용 ; -라고 :라고부터만이라도*/
#define QUIFROINDNSE     1033       /* 간접인용 ; -고   :고부터만이라도  */
#define CAUFROINDNSE     1034       /* 원인 ; -에,(으)로:에부터만이라도  */
#define SPL_TOINDTOP     1040       /* 장소 ; 에,에서   :에서까지만은    */
#define TML_TOINDTOP     1041       /* 시간 ; 에        :에까지만은      */
#define STL_TOINDTOP     1042       /* 행위귀착 ; 에,...:에게까지만은    */
#define SRC_TOINDTOP     1043       /* 출발점 ; 에게,...:에서까지만은    */
#define GOA_TOINDTOP     1044       /* 지향점 ; (으)로,.:으로까지만은    */
#define FOL_TOINDTOP     1045       /* 도구 ; (으)로(써):으로써까지만은  */
#define QUL_TOINDTOP     1046       /* 자격 ; (으)로(서):으로서까지만은  */
#define CHA_TOINDTOP     1047       /* 바뀜 ; (으)로    :으로까지만은    */
#define CM__TOINDTOP     1048       /* 단순비교 ; 과,와 :과까지만은      */
#define CME_TOINDTOP     1049       /* 동등비교 ; 만큼  :만큼까지만은    */
#define CMS_TOINDTOP     1050       /* 그 같음 ; 처럼   :처럼까지만은    */
#define CMP_TOINDTOP     1051       /* 상대비교 ; 보다  :보다까지만은    */
#define QUD_TOINDTOP     1052       /* 직접인용 ; -라고 :라고까지만은    */
#define QUI_TOINDTOP     1053       /* 간접인용 ; -고   :고까지만은      */
#define CAU_TOINDTOP     1054       /* 원인 ; -에,(으)로:에까지만은      */
#define SPL_TOINDNSE     1060       /* 장소 ; 에,에서   :에서까지만이라도*/
#define TML_TOINDNSE     1061       /* 시간 ; 에        :에까지만이라도  */
#define STL_TOINDNSE     1062       /* 행위귀착 ; 에,...:에게까지만이라도*/
#define SRC_TOINDNSE     1063       /* 출발점 ; 에게,...:에서까지만이라도*/
#define GOA_TOINDNSE     1064       /* 지향점 ; (으)로,.:으로까지만이라도*/
#define FOL_TOINDNSE     1065       /* 도구 ; (으)로(써):으로써까지만이..*/
#define QUL_TOINDNSE     1066       /* 자격 ; (으)로(서):으로서까지만이..*/
#define CHA_TOINDNSE     1067       /* 바뀜 ; (으)로    :으로까지만이라도*/
#define CM__TOINDNSE     1068       /* 단순비교 ; 과,와 :과까지만이라도  */
#define CME_TOINDNSE     1069       /* 동등비교 ; 만큼  :만큼까지만이라도*/
#define CMS_TOINDNSE     1070       /* 그 같음 ; 처럼   :처럼까지만이라도*/
#define CMP_TOINDNSE     1071       /* 상대비교 ; 보다  :보다까지만이라도*/
#define QUD_TOINDNSE     1072       /* 직접인용 ; -라고 :라고까지만이라도*/
#define QUI_TOINDNSE     1073       /* 간접인용 ; -고   :고까지만이라도  */
#define CAU_TOINDNSE     1074       /* 원인 ; -에,(으)로:에까지만이라도  */
#define SPL_TONOMTOP     1080       /* 장소 ; 에,에서   :에서까지밖에는  */
#define TML_TONOMTOP     1081       /* 시간 ; 에        :에까지밖에는    */
#define STL_TONOMTOP     1082       /* 행위귀착 ; 에,...:에게까지밖에는  */
#define SRC_TONOMTOP     1083       /* 출발점 ; 에게,...:에서까지밖에는  */
#define GOA_TONOMTOP     1084       /* 지향점 ; (으)로,.:으로까지밖에는  */
#define FOL_TONOMTOP     1085       /* 도구 ; (으)로(써):으로써까지밖에는*/
#define QUL_TONOMTOP     1086       /* 자격 ; (으)로(서):으로서까지밖에는*/
#define CHA_TONOMTOP     1087       /* 바뀜 ; (으)로    :으로까지밖에는  */
#define CM__TONOMTOP     1088       /* 단순비교 ; 과,와 :과까지밖에는    */
#define CME_TONOMTOP     1089       /* 동등비교 ; 만큼  :만큼까지밖에는  */
#define CMS_TONOMTOP     1090       /* 그 같음 ; 처럼   :처럼까지밖에는  */
#define CMP_TONOMTOP     1091       /* 상대비교 ; 보다  :보다까지밖에는  */
#define QUD_TONOMTOP     1092       /* 직접인용 ; -라고 :라고까지밖에는  */
#define QUI_TONOMTOP     1093       /* 간접인용 ; -고   :고까지밖에는    */
#define CAU_TONOMTOP     1094       /* 원인 ; -에,(으)로:에까지밖에는    */
#define SPLINDINDTOP     1100       /* 장소 ; 에,에서   :에서뿐만은      */
#define TMLINDINDTOP     1101       /* 시간 ; 에        :에뿐만은        */
#define STLINDINDTOP     1102       /* 행위귀착 ; 에,...:에뿐만은        */
#define SRCINDINDTOP     1103       /* 출발점 ; 에게,...:에뿐만은        */
#define GOAINDINDTOP     1104       /* 지향점 ; (으)로,.:으로뿐만은      */
#define FOLINDINDTOP     1105       /* 도구 ; (으)로(써):으로써뿐만은    */
#define QULINDINDTOP     1106       /* 자격 ; (으)로(서):으로서뿐만은    */
#define CHAINDINDTOP     1107       /* 바뀜 ; (으)로    :으로뿐만은      */
#define CM_INDINDTOP     1108       /* 단순비교 ; 과,와 :과뿐만은        */
#define CMEINDINDTOP     1109       /* 동등비교 ; 만큼  :만큼뿐만은      */
#define CMSINDINDTOP     1110       /* 그 같음 ; 처럼   :처럼뿐만은      */
#define CMPINDINDTOP     1111       /* 상대비교 ; 보다  :보다뿐만은      */
#define QUDINDINDTOP     1112       /* 직접인용 ; -라고 :라고뿐만은      */
#define QUIINDINDTOP     1113       /* 간접인용 ; -고   :고뿐만은        */
#define CAUINDINDTOP     1114       /* 원인 ; -에,(으)로:에뿐만은        */
#define SPLINDINDNSE     1120       /* 장소 ; 에,에서   :에서뿐만이라도  */
#define TMLINDINDNSE     1121       /* 시간 ; 에        :에뿐만이라도    */
#define STLINDINDNSE     1122       /* 행위귀착 ; 에,...:에뿐만이라도    */
#define SRCINDINDNSE     1123       /* 출발점 ; 에게,...:에뿐만이라도    */
#define GOAINDINDNSE     1124       /* 지향점 ; (으)로,.:으로뿐만이라도  */
#define FOLINDINDNSE     1125       /* 도구 ; (으)로(써):으로써뿐만이라도*/
#define QULINDINDNSE     1126       /* 자격 ; (으)로(서):으로서뿐만이라도*/
#define CHAINDINDNSE     1127       /* 바뀜 ; (으)로    :으로뿐만이라도  */
#define CM_INDINDNSE     1128       /* 단순비교 ; 과,와 :과뿐만이라도    */
#define CMEINDINDNSE     1129       /* 동등비교 ; 만큼  :만큼뿐만이라도  */
#define CMSINDINDNSE     1130       /* 그 같음 ; 처럼   :처럼뿐만이라도  */
#define CMPINDINDNSE     1131       /* 상대비교 ; 보다  :보다뿐만이라도  */
#define QUDINDINDNSE     1132       /* 직접인용 ; -라고 :라고뿐만이라도  */
#define QUIINDINDNSE     1133       /* 간접인용 ; -고   :고뿐만이라도    */
#define CAUINDINDNSE     1134       /* 원인 ; -에,(으)로:에뿐만이라도    */
