var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var users = new Schema ({
	email:String,
	name: String,
	password: String,
	auth: String
});
exports.users= mongoose.model('users', users);

var posts = new Schema({
	//user:{type: Schema.ObjectId, ref: 'users'},
	userName: String,
	accessLevel: String,
	date:Date,
	title:String,
	content:String,
	tag:[String],
	comment:[{type:Schema.ObjectId, ref:"comments"}]
});

var comments = new Schema({
	userName:String,
	post:{ type:Schema.ObjectId, ref:"posts"},
	content:String,
	date:Date,
	parent:{ type:Schema.ObjectId, ref:"comments"}
});


exports.posts= mongoose.model('posts', posts);
exports.comments = mongoose.model('comments', comments);