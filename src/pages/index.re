let drawerWidth = 700;

let style = ReactDOMRe.Style.make;
/* module ThemeHelpers = MaterialUi_ThemeHelpers; */

[%mui.withStyles
  "Styles"({
    root:
      style(
        ~display="flex",
        ~overflow="hidden",
        ~height="100%",
        (),
      ),
    content:
      style(
        ~flexGrow="1",
        ~transition="margin 195ms ease-in",
        /* ~transition= */
        /*   ThemeHelpers.transitionCreate( */
        /*     ~theme, */
        /*     ~affectWidth=false, */
        /*     ~affectMargin=true, */
        /*     ~easing="cubic-bezier(0.4, 0, 0.6, 1)", */
        /*     ~duration=195.0, */
        /*     (), */
        /*   ), */
        ~marginRight=string_of_int(-drawerWidth) ++ "px",
        ~marginLeft=string_of_int(-drawerWidth) ++ "px",
        (),
      ),
    contentShiftLeft:
      style(
        /* ~transition= */
        /*   ThemeHelpers.transitionCreate( */
        /*     ~theme, */
        /*     ~affectWidth=false, */
        /*     ~affectMargin=true, */
        /*     ~easing="cubic-bezier(0.4, 0, 1, 1)", */
        /*     ~duration=195.0, */
        /*     (), */
        /*   ), */
        ~transition="margin 195ms ease-out",
        ~marginLeft="0px",
        (),
      ),
    contentShiftRight:
      style(
        /* ~transition= */
        /*   ThemeHelpers.transitionCreate( */
        /*     ~theme, */
        /*     ~affectWidth=false, */
        /*     ~affectMargin=true, */
        /*     ~easing="cubic-bezier(0.4, 0, 1, 1)", */
        /*     ~duration=195.0, */
        /*     (), */
        /*   ), */
        ~transition="margin 195ms ease-out",
        ~marginRight="0px",
        ~display="flex",
        ~overflow="hidden",
        ~height="100%",
        (),
      ),
    overflowVis:
      style(
        ~overflow="visible",
        (),
      ),
    grid:
      style(
        ~width="100%",
        ~height="100%",
        (),
      ),
    leftButton:
      style(
        ~position="absolute",
        ~top="50%",
        ~left="2%",
        ~transform="translate(-2%, -50%)",
        ~color="red",
        (),
      ),
    hide:
      style(
        ~display="none",
        (),
      ),
    rightButton:
      style(
        ~position="absolute",
        ~top="50%",
        ~right="2%",
        ~transform="translate(2%, -50%)",
        ~color="red",
        (),
      ),
    bgImage:
      style(
        ~height="100%",
        ~width="100%",
        ~overflow="hidden",
        ~objectFit="cover",
        ~objectPosition="center",
        (),
      ),
    name:
      style(
        ~position="absolute",
        ~top="50%",
        ~left="50%",
        ~transform="translate(-50%, -50%)",
        (),
      ),
  })
];

let videoStart = 1;
let firstBreakpoint = 49;
let secondBreakpoint = 99;
let videoEnd = 148;

type breakPoint = {reverse: bool, frame: int};
type contentVariant =
  | About
  | Projects;

// Helper function to determine the frames
let findNextBreakPoint = (~currImageNumber, ~contentClicked) => {
  switch (contentClicked) {
    | (About) when currImageNumber > firstBreakpoint => { reverse: true, frame: 49 }
    | (About) when currImageNumber < firstBreakpoint => { reverse: false, frame: 49 }
    | (About) when currImageNumber == firstBreakpoint => { reverse: false, frame: 49 }
    | (Projects) when currImageNumber > secondBreakpoint => { reverse: true, frame: 99 }
    | (Projects) when currImageNumber < secondBreakpoint => { reverse: false, frame: 99 }
    | (Projects) when currImageNumber == secondBreakpoint => { reverse: false, frame: 99 }
    | _ => raise(Not_found)
  }
};

let setInterval = (timeout, action) => {
  let intervalIdRef = ref(None);
  let clear = () =>
    switch (intervalIdRef^) {
      | Some(intervalId) => Js.Global.clearInterval(intervalId);
      | None => ()
    }

  let intervalId = Js.Global.setInterval(() => action(~clear), timeout);
  intervalIdRef := Some(intervalId);

  // return id outside as well
  intervalId;
};

// Global state of timers
let leftTimer = ref(None);
let rightTimer = ref(None);

[@react.component]
let make = () => {
  let (openLeft, setOpenLeft) = React.useState(() => false);
  let (openRight, setOpenRight) = React.useState(() => false);
  let (imageNumber, setImageNumber) = React.useState(() => 1);


  let handleLeftDrawerOpen = (_) => {
    switch (leftTimer^) {
      | Some(intervalId) => Js.Global.clearInterval(intervalId);
      | None => ()
    }
    switch (rightTimer^) {
      | Some(intervalId) => Js.Global.clearInterval(intervalId);
      | None => ()
    }

    setOpenLeft(_ => true);
    setOpenRight(_ => false);
    let { reverse, frame } = findNextBreakPoint(~currImageNumber=imageNumber, ~contentClicked=About);

    let intervalId = setInterval(1000 / 24, (~clear) => {
      setImageNumber((prevImage) => {
        if (prevImage === frame) {
          clear();
          prevImage;
        } else {
          let newFrame = reverse ? prevImage - 1 : prevImage + 1;

          switch(newFrame > videoEnd, newFrame < videoStart, newFrame) {
            | (true, false, _) => videoEnd
            | (false, true, _) => videoStart
            | (_, _,newFrame) => newFrame
          };
        }
      });
    });

    leftTimer := Some(intervalId);
  };

  let handleLeftDrawerClose = (_) => {
    setOpenLeft(_ => false);
  };

  let handleRightDrawerOpen = (_) => {
    switch (leftTimer^) {
      | Some(intervalId) => Js.Global.clearInterval(intervalId);
      | None => ()
    }
    switch (rightTimer^) {
      | Some(intervalId) => Js.Global.clearInterval(intervalId);
      | None => ()
    }

    setOpenRight(_ => true);
    setOpenLeft(_ => false);
    let { reverse, frame } = findNextBreakPoint(~currImageNumber=imageNumber, ~contentClicked=Projects);

    let intervalId = setInterval(1000 / 24, (~clear) => {
      setImageNumber((prevImage) => {
        if (prevImage === frame) {
          clear();
          prevImage;
        } else {
          let newFrame = reverse ? prevImage - 1 : prevImage + 1;

          switch(newFrame > videoEnd, newFrame < videoStart, newFrame) {
            | (true, false, _) => videoEnd
            | (false, true, _) => videoStart
            | (_, _,newFrame) => newFrame
          };
        }
      });
    });

    rightTimer := Some(intervalId);
  };

  let handleRightDrawerClose = (_) => {
    setOpenRight(_ => false);
  };

  <ThemeSetup>
    MaterialUi.(
      <div style={style(~height="100%", ())}>
        <Styles>
          ...{classes =>
            <Hidden mdDown=false>
              <div className={Cn.make([classes.root, classes.overflowVis->Cn.ifTrue(openLeft || openRight)])}>
                <AboutDrawer openLeft=openLeft handleLeftDrawerClose=handleLeftDrawerClose />
                <main className={Cn.make([classes.content,
                  classes.contentShiftLeft->Cn.ifTrue(openLeft),
                  classes.contentShiftRight->Cn.ifTrue(openRight),
                ])}>
                  <Grid container=true spacing=V0 className={classes.grid}>
                    <Button
                      onClick={handleLeftDrawerOpen}
                      className={Cn.make([classes.leftButton, classes.hide->Cn.ifTrue(openLeft)])}
                      startIcon={
                        <MscharleyBsMaterialUiIcons.ChevronLeft.Outlined
                          style={style(
                              ~fontSize="48px",
                              (),
                          )}
                        />
                      }
                    >
                      {"About"->React.string}
                    </Button>
                    {!openLeft && !openRight ?
                      <Typography className={classes.name} variant=`H1 align=`Center>
                        {"Taylor King."->React.string}
                      </Typography>
                      : ReasonReact.null
                    }
                    <img src={"/me-" ++ string_of_int(imageNumber) ++ ".jpg"} className={classes.bgImage} />
                    <Button onClick={handleRightDrawerOpen} className={classes.rightButton} endIcon={
                      <MscharleyBsMaterialUiIcons.ChevronRight.Outlined
                        style={style(
                            ~fontSize="48px",
                            (),
                        )}
                      />
                      }
                    >
                      {"Work"->React.string}
                    </Button>
                  </Grid>
                </main>
                <WorkDrawer openRight=openRight handleRightDrawerClose=handleRightDrawerClose />
              </div>
            </Hidden>
          }
        </Styles>
      </div>
    )
  </ThemeSetup>
};

let default = make;
