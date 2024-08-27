// import 'package:flutter/foundation.dart';
// import 'package:flutter/material.dart';
// import 'package:firebase_core/firebase_core.dart';
// import 'welcome_screen.dart';
// import 'home_screen.dart';
// import 'signup_screen.dart';
// import 'login_screen.dart';

// void main() async {
//   WidgetsFlutterBinding.ensureInitialized();
//   if (kIsWeb) {
//     // Initialize Firebase with your configuration
//     await Firebase.initializeApp(
//       options: const FirebaseOptions(
//           apiKey: "AIzaSyDV6dKjE1GTTUdKsdzo1FDlWLns7kkn_0M",
//           authDomain: "iot5-d707d.firebaseapp.com",
//           projectId: "iot5-d707d",
//           storageBucket: "iot5-d707d.appspot.com",
//           messagingSenderId: "136590850189",
//           appId: "1:136590850189:web:d5d792c25167c3f3938ac4",
//           measurementId: "G-VHJS3R80QK"),
//     );
//   } else {
//    await Firebase.initializeApp();
//   }
//   runApp(MyApp());
// }

// class MyApp extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       initialRoute: 'welcome_screen',
//       routes: {
//         'welcome_screen': (context) => WelcomeScreen(),
//         'registration_screen': (context) => RegistrationScreen(),
//         'login_screen': (context) => LoginScreen(),
//         'home_screen': (context) => HomeScreen(),
//       },
//     );
//   }
// }

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter_firebase1/LandingScreen/landing_screen.dart';
import 'package:flutter_firebase1/SensorScreen/sensor_screen.dart';
import 'package:flutter_firebase1/user_model.dart';
import 'package:provider/provider.dart';
import 'welcome_screen.dart';
import 'home_screen.dart';
import 'signup_screen.dart';
import 'login_screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  if (kIsWeb) {
    // Initialize Firebase for web
    await Firebase.initializeApp(
      options: const FirebaseOptions(
        apiKey: "AIzaSyDV6dKjE1GTTUdKsdzo1FDlWLns7kkn_0M",
        authDomain: "iot5-d707d.firebaseapp.com",
        projectId: "iot5-d707d",
        storageBucket: "iot5-d707d.appspot.com",
        messagingSenderId: "136590850189",
        appId: "1:136590850189:web:d5d792c25167c3f3938ac4",
        measurementId: "G-VHJS3R80QK",
      ),
    );
  } else {
    // Initialize Firebase for mobile
    await Firebase.initializeApp();
  }

  runApp(
    ChangeNotifierProvider(
      create: (context) => UserModel(),
      child: MyApp(),
    ),
  );
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      initialRoute: 'welcome_screen',
      routes: {
        'welcome_screen': (context) => WelcomeScreen(),
        'registration_screen': (context) => RegistrationScreen(),
        'login_screen': (context) => LoginScreen(),
        'home_screen': (context) => HomeScreen(),
        'landing': (context) => LandingScreen(),
        'sensor': (context) => SensorScreen(),
      },
    );
  }
}
