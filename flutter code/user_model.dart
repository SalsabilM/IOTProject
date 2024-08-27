// // user_model.dart
// import 'package:flutter/material.dart';

// class UserModel extends ChangeNotifier {
//   String _name = '';

//   String get name => _name;

//   void setName(String name) {
//     _name = name;
//     notifyListeners();
//   }
// }
//222222222222222222222222222222222222222222222222222222222222222222222222222222

import 'package:flutter/foundation.dart';

class UserModel extends ChangeNotifier {
  String _name = '';

  String get name => _name;

  void setName(String newName) {
    _name = newName;
    notifyListeners();
  }
}
