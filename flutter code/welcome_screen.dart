// import 'package:flutter/material.dart';
// import 'rounded_button.dart';

// class WelcomeScreen extends StatefulWidget {
//   @override
//   _WelcomeScreenState createState() => _WelcomeScreenState();
// }

// class _WelcomeScreenState extends State<WelcomeScreen> {
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//         backgroundColor: Colors.white,
//         body: Padding(
//           padding: EdgeInsets.symmetric(horizontal: 24.0),
//           child: Column(
//               mainAxisAlignment: MainAxisAlignment.center,
//               crossAxisAlignment: CrossAxisAlignment.stretch,
//               children: <Widget>[
//                 RoundedButton(
//                   colour: Colors.lightBlueAccent,
//                   title: 'Log In',
//                   onPressed: () {
//                     Navigator.pushNamed(context, 'login_screen');
//                   },
//                 ),
//                 RoundedButton(
//                     colour: Colors.blueAccent,
//                     title: 'Register',
//                     onPressed: () {
//                       Navigator.pushNamed(context, 'registration_screen');
//                     }),
//               ]),
//         ));
//   }
// }

//222222222222222222222222222222222222222222222222222222222222222222222222222222

// import 'package:flutter/material.dart';

// class WelcomeScreen extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Welcome'),
//       ),
//       body: Center(
//         child: Column(
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: [
//             Text('Welcome to the App!'),
//             SizedBox(height: 20),
//             ElevatedButton(
//               onPressed: () {
//                 Navigator.pushNamed(context, 'login_screen');
//               },
//               child: Text('Login'),
//             ),
//             ElevatedButton(
//               onPressed: () {
//                 Navigator.pushNamed(context, 'registration_screen');
//               },
//               child: Text('Register'),
//             ),
//           ],
//         ),
//       ),
//     );
//   }
// }

//222222222222222222222222222222222222222222222222222222222222222222222222222222

import 'package:flutter/material.dart';
import 'package:flutter_firebase1/constants.dart';

class WelcomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size;

    return Scaffold(
      appBar: AppBar(
        title: Text('Smart Home'),
        backgroundColor: kBgColor, // Customize the color
        elevation: 0,
        centerTitle: true,
      ),
      body: Center(
        child: Padding(
          padding: EdgeInsets.symmetric(horizontal: size.width * 0.1),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              // Logo section
              // Image.asset(
              //   'assets/images/logo.png',
              //   height: 120, // Adjust the height as needed
              // ),
              SizedBox(height: 20),
              Text(
                'Welcome to Smart Home',
                style: TextStyle(
                  fontSize: 24,
                  fontWeight: FontWeight.bold,
                  color: Colors.black87,
                ),
              ),
              SizedBox(height: 40),
              ElevatedButton(
                onPressed: () {
                  Navigator.pushNamed(context, 'login_screen');
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: kDarkGreyColor, // Button color
                  padding: EdgeInsets.symmetric(vertical: 15, horizontal: 30),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(30),
                  ),
                ),
                child: Text(
                  'Login',
                  style: TextStyle(fontSize: 18),
                ),
              ),
              SizedBox(height: 20),
              ElevatedButton(
                onPressed: () {
                  Navigator.pushNamed(context, 'registration_screen');
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.grey, // Button color
                  padding: EdgeInsets.symmetric(vertical: 15, horizontal: 30),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(30),
                  ),
                ),
                child: Text(
                  'Register',
                  style: TextStyle(fontSize: 18),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
