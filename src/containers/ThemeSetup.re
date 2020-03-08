let theme =
  MaterialUi.Theme.create(
    MaterialUi.ThemeOptions.(
      make(
        ~palette=
          PaletteOptions.make(
            ~primary=Primary.make(~main="#556cd6", ()),
            ~secondary=Secondary.make(~main="#19857b", ()),
            (),
          ),
        (),
        ~typography=
          Typography.make(
            ~h1=TypographyStyleOptions.make(~color="red", ~fontFamily="Karla, Arial", ()),
            ~h2=TypographyStyleOptions.make(~fontFamily="Karla, Arial", ()),
            ~h6=TypographyStyleOptions.make(~color="red", ~fontFamily="Karla, Arial", ()),
            (),
          ),
        /* ~transitions= */
        /*   TransitionsOptions.make( */
        /*     ~easing=Easing.make( */
        /*       ~easeIn="cubic-bezier(0.4, 0, 0.2, 1)", */
        /*       ~easeInOut="cubic-bezier(0.0, 0, 0.2, 1)", */
        /*       ~easeOut="cubic-bezier(0.4, 0, 1, 1)", */
        /*       ~sharp="cubic-bezier(0.4, 0, 0.6, 1)", */
        /*       (), */
        /*     ), */
        /*     ~duration=Duration.make( */
        /*       ~leavingScreen=195.0, */
        /*       (), */
        /*     ), */
        /*     (), */
        /*   ) */
      )
    ),
  );


[@react.component]
let make = (~children) => {
  MaterialUi.(
    <MuiThemeProvider theme> children </MuiThemeProvider>
  );
};
